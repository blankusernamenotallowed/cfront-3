# cfront source map — where to start reading

cfront is a **multi-pass C++ → C translator** (~54k lines of pre-standard C++ in
`src/`). It is not a compiler back end: it parses C++, type-checks it, lowers it
to a C-level tree, and prints C. A separate C compiler then builds that C.

This document explains the architecture and gives you a reading order so the
source isn't a wall of 34 `.C` files.

---

## 1. The 10,000-foot view: one pipeline, driven from `main.C`

The whole compiler is the loop in **`src/main.C : run()`** (line ~113). For each
top-level declaration it runs four phases:

```
              ┌─────────── src/main.C  run() ───────────┐
   C++ text → │ syn() → dcl() → simpl() → print()        │ → C text
              └──────────────────────────────────────────┘
   (cpp)        parse   typecheck  lower     emit
```

```c
while (n = syn()) {         // 1. PARSE   one declaration into a node tree
    n->dcl(gtbl, EXTERN);   // 2. TYPECHECK: bind names, resolve types/overloads
    n->simpl();             // 3. SIMPLIFY: lower C++ constructs to C-level tree
    n->dcl_print();         // 4. PRINT:   walk the tree and emit C
}
```

Everything else in `src/` is the implementation of those four verbs for the many
kinds of node. **If you read only one function first, read `run()`.**

The `CC` / `CC3` shell script is the *driver* around the `cfront` binary: it runs
the C preprocessor, pipes the result into `cfront`, then compiles the emitted C
and runs `munch` to collect static constructors. cfront itself only does
stdin (preprocessed C++) → stdout (C).

---

## 2. The data model: everything is a `node`

Defined in **`src/cfront.h`** (the ~1300-line master header — skim it early).
The whole program is a tree of `node`s. The base class carries a **`TOK base`
field that discriminates the exact kind** (e.g. an `expr` with `base==PLUS` vs
`base==CALL`):

```
node                         (cfront.h:177 — has `TOK base`, the discriminator)
├── type                     a C++ type
│   ├── basetype             int/char/class-ref/…            (BASETYPE)
│   ├── fct                  a function type                 (FCT)
│   ├── pvtyp → ptr, vec     pointer / reference / array     (PTR, RPTR, VEC)
│   ├── classdef             a class/struct/union            (CLASS)
│   ├── enumdef              an enum                         (ENUM)
│   └── gen                  an overload set                 (OVERLOAD)
├── expr                     an expression (PLUS, CALL, …)
│   ├── name                 ⭐ a declared name (var/fn/type) (NAME, TNAME)
│   ├── call, ref, cast, qexpr, ival, mdot, …
├── stmt                     a statement
│   ├── block                { decls; stmts; }               (BLOCK)
│   ├── estmt, ifstmt, forstmt, lstmt, pair
├── table / ktable           symbol tables (scopes)
└── virt, basecl, name_list  vtable entries, base classes, lists
```

Two things surprise everyone:

- **`name` is a subclass of `expr`.** `Pname` (a `name*`) is the universal handle
  for "a declared thing" — variables, functions, types, members all are `name`s.
  See the `Pxxx` typedefs in **`src/typedef.h`** (`Pname`, `Ptype`, `Pexpr`,
  `Pstmt`, `Pclass`, `Pfct`, …). These pointer names are used *everywhere*.
- **Methods switch on `base`, they are not C++-virtual.** To see how a `PLUS`
  node prints, open `expr::print` in `print.C` and find `case PLUS`. A node
  "class" (e.g. `expr`) implements a phase (e.g. `print`) once, as a big switch.

So each phase is spread across files *by node family*, and within a file it is a
switch over `base`.

---

## 3. Recommended reading order

1. **`src/main.C` → `run()`** — the pipeline (above). ~1 page.
2. **`src/cfront.h`** — skim the `struct` declarations (§2). Don't read bodies;
   just learn the node zoo and the `base` field. Also glance at `typedef.h`.
3. **`src/token.h`** — the token/keyword numbers and the node "kinds" (`PLUS`,
   `CALL`, `CLASS`, `FCT`, …) that fill the `base` field.
4. **`src/gram.y`** — the yacc grammar: which C++ syntax builds which nodes. Read
   the rules, skim the actions.
5. Pick **one feature and trace it through the four phases** (see §6).

Everything below is reference for step 5.

---

## 4. File map, grouped by phase

Line counts in parentheses. Generated files are marked.

### Driver, entry, errors
| file | role |
|------|------|
| `main.C` (900) | entry point, option parsing, **`run()`** pipeline, output of the `__ptbl_vec__`/ctor plumbing |
| `error.C` (787) | `error()` (the printf-like diagnostic engine with `%n %t %k` formats) and `yyerror` |
| `../CC3` (shell) | the *driver*: cpp → cfront → cc → munch. Not C++ |

### Phase 1 — Lexing & parsing
| file | role |
|------|------|
| `lex.C` (1438) | the raw lexer `tlex()` — characters → tokens, keyword table |
| `lalex.C` (1820) | the **look-ahead lexer** `lalex()` — cfront's lexer is context-sensitive (it decides ID vs TNAME by symbol-table lookup), so it buffers a token queue |
| `token.h` / `tqueue.h` | token numbers; the token-queue node |
| `gram.y` (2600) | the **yacc grammar** + semantic actions that build the node tree |
| `y.tab.C` (6982) *(generated)* | the parser tables from `gram.y` (via bison). Don't read; regenerated by the Makefile |
| `yystype.h` *(generated)* | the `YYSTYPE` union + token `#define`s |
| `norm.C` (2146), `norm2.C` (295) | **normalization** — post-parse cleanup the grammar was too clumsy to do inline |

> Heads-up: there are **two token-numbering systems** — `token.h` (used by the
> lexer/back end) and `yystype.h` (the grammar's). They share names with matching
> values. This is exactly where the build fix in `BUILD-WINDOWS.md` lives.

### The symbol tables & name lookup
| file | role |
|------|------|
| `table.C` (419) | `table` / `ktable` — hashed scope tables (`look`, `insert`) |
| `hash.C`/`hash.h` (351) | the generic hash table used by the tables |
| `find.C` (1781) | **name lookup & visibility** — the heart of scope/overload resolution |
| `block.C`/`Block.h` | block-scope helpers |

### Phase 2 — Declaration & type checking (`dcl` / `typ`)
This is the largest phase — binding names, computing sizes, checking types,
resolving overloads.
| file | role |
|------|------|
| `dcl.C` (2092) | **`name::dcl`** — declare names into tables, compute object/frame sizes |
| `dcl2.C`–`dcl4.C` (1518/3111/2879) | class members, base classes, ctors/dtors, conversions, more declaration logic |
| `expr.C`,`expr2.C`,`expr3.C` (2583/2731/2694) | **`expr::typ`** — type-check expressions, insert implicit conversions/coercions |
| `typ.C`/`typ2.C` (1317/544) | type utilities: type compatibility (`check`), the built-in types |
| `size.C`/`size.h` (324) | object layout: `sizeof`/alignment constants (fed by `szal.result`) |
| `repr.C` (246) | string representation of operators (name mangling helpers) |
| `discrim.C` (353) | node "union discriminator" sanity helpers |

### Phase 3 — Simplification / lowering (`simpl`)
Turns C++ semantics into a C-level tree: virtual calls → vtable indexing, `new`/
`delete` → function calls, ctors/dtors inserted, references → pointers, etc.
| file | role |
|------|------|
| `simpl.C`/`simpl2.C` (1292/2785) | **`name::simpl` / `fct::simpl` / `expr::simpl`** — the lowering pass |
| `expand.C` (1108) | inline-function expansion |
| `del.C` (310) | freeing/`delete` machinery and node teardown |

### Phase 4 — Code generation (`print`)
| file | role |
|------|------|
| `print.C` (1399) | **`expr::print` / `stmt::print`** — emit C for expressions & statements |
| `print2.C` (2543) | emit C for declarations, classes, the `__vtbl__`/`__mptr` vtables |

### Templates (a bolted-on subsystem)
| file | role |
|------|------|
| `template.C` (4734), `template.h` | template parsing, matching, instantiation |
| `tree_copy.C`/`tree_walk.C` (324/1234) | deep-copy / walk node trees to instantiate templates |

### Support
| file | role |
|------|------|
| `alloc.C` (382) | custom per-node-type allocators (free lists; see `operator new`) |
| `Bits.C`/`Bits.h` (433) | bit-vector utility |
| `_stdio.c` | tiny stdio glue |

---

## 5. Two mental models you need

**`error()` is the debugger.** `src/error.C`'s `error()` uses custom formats:
`%n` = name, `%t` = type, `%k` = token/kind, `%e` = expr. Grep for `error('d',…)`
(the 'd' = debug severity) — the source is littered with commented-out `error('d',…)`
trace calls that document what each function is doing. Uncommenting them (and
building with `DBG`) is how the authors debugged it.

**The `base` field is the type tag.** Any time you have a `node*`/`Pexpr`/`Ptype`
and wonder "what is it really?", it's `->base`. The switch statements over `base`
in each phase are the real control flow.

---

## 6. A worked example: follow `class Dog : public Animal` through the source

Use this as a template for tracing any feature:

1. **Parse** — `gram.y` rule `class_dcl` (and `class_head`, `base_spec`) builds a
   `classdef` node; `norm.C` tidies it.
2. **Typecheck** — `name::dcl` (`dcl.C`) inserts `Dog` into `gtbl`; class-member
   and base-class handling is in `dcl2.C`/`dcl3.C`; `size.C` lays out the struct
   and assigns the vtable slot; overload/lookup via `find.C`.
3. **Simplify** — `simpl2.C` inserts the constructor/destructor calls and turns
   `virtual` calls into vtable indexing; `expand.C` inlines the small bodies.
4. **Print** — `print2.C` emits `struct Dog {…}`, the `__vtbl__3Dog__…[]` table,
   and the `__dt__3DogFv` etc. functions (compare with `demo/zoo-cpp-vs-c.md`,
   which shows exactly this output).

To find "who does X", grep for the emitted artifact: e.g. the vtable symbol
`__vtbl` or `__ptbl_vec` → leads you into `print2.C` and `simpl2.C`.

---

## 7. Handy grep recipes

```sh
# where is a node method implemented?
grep -n 'expr::print\|stmt::print\|name::dcl\|fct::simpl' src/*.C

# what does base==<KIND> mean / where is it handled?
grep -rn 'case CALL' src/*.C           # e.g. the CALL node in each phase

# the built-in types (int_type, char_type, …) are created here:
grep -n '_type *=' src/typ.C src/size.C

# name mangling / operator spelling:
less src/repr.C
```

Start with `main.C:run()` and `cfront.h`, keep `demo/zoo-cpp-vs-c.md` open to see
the output side, and trace one feature at a time. That's the fastest way in.
