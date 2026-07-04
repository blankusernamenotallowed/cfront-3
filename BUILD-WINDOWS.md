# Building cfront-3 on Windows (MSYS2)

This document records how cfront-3 was made to build and run on Windows, and the
fixes that were required. cfront is a ~1991 C++→C translator; getting it to
compile with a modern (GCC 15) toolchain on a 64-bit LP64 target took a number of
changes.

## Toolchain

cfront is a POSIX program (needs `sys/wait.h`, `unistd.h`, `fork`-style headers via
`osfcn.h`). The **MSYS2 POSIX/Cygwin toolchain** is required — not mingw64, which
lacks these headers.

```
pacman -S --needed gcc bison make      # in the MSYS2 (msys) subsystem
```

Compilers used:
- `/c/msys64/usr/bin/g++`   (GCC 15.x, cygwin/LP64 — `long` and pointers are 8 bytes)
- `/c/msys64/usr/bin/gcc`   (for szal, munch, and as cfront's cpp/cc backend)
- `/c/msys64/usr/bin/bison` (3.8; `yacc` wrapper is broken — call bison directly)

## Build procedure

```sh
export PATH="/c/msys64/usr/bin:$PATH"

# 1. incl/ must be a symlink/junction to incl-master/incl-linux32.
#    MSYS `ln -s` may copy instead of link; use a junction so edits propagate:
cmd //c "mklink /J incl incl-master\incl-linux32"

# 2. Build the translator.
make -C src CXX=/c/msys64/usr/bin/g++.exe      # produces src/cfront.exe, copied to ./

# 3. Build munch (K&R C — needs legacy mode).
gcc -std=gnu89 -w -o munch _munch/munch.c

# 4. Build the runtime library and demo via the CC driver (./CC -> CC3).
```

## Fixes applied (why each was needed)

- **`src/szal.result`** — regenerated with the *cygwin* gcc. The type-size table
  drives cfront's whole type model. It was originally generated with mingw gcc
  (LLP64, `long`=4); the real target is LP64 (`long`=8). The mismatch made
  cfront's `size_t` 4 bytes and broke `operator new` type-checking.
- **`src/gram.y`**
  - Two mid-rule `$$` assignments tagged `$<pn>$` (bison 3.x requires a type for
    mid-rule values that are later referenced by type).
  - Forward declarations for the static grammar-action helpers defined at the end
    of the file (`enumcheck`, `check_tag`, `hoist_al`, `arg_redec`, `dummy_dtor`,
    `check_if_base`) — modern C++ forbids implicit declarations.
  - `yyval` made a real global (classic-yacc semantics; `lalex.C` peeks at it).
- **`src/Makefile`**
  - `CCFLAGS`: `-fpermissive -std=gnu++98 -w -fno-strict-aliasing
    -ftrivial-auto-var-init=zero`.
  - Post-`yacc` seds: disable bison's `enum yytokentype` (token.h already provides
    the same tokens as `#define`s, which collide with the enum), and bind the
    parser's local `yyval` to the global.
- **`src/template.h`** — default argument moved off the `friend` declaration of
  `has_templ_instance` onto a namespace-scope declaration.
- **`src/gram.y` + `src/lalex.C` — the `NEXTTOK()` / `yychar` empty sentinel.**
  This was the big one. Classic yacc used **-1** as the "no lookahead yet"
  sentinel for `yychar`; modern **bison uses `YYEMPTY` = -2**. cfront's
  context-sensitive lexer peeks at the next token with
  `#define NEXTTOK() ((yychar==-1)? yychar=yylex() : yychar)` and also does
  `yychar = -1` to force a refetch. Under bison, `yychar` is -2 after a default
  reduction, so `NEXTTOK()` thought a token was already present and returned the
  -2 sentinel as if it were a real token — which derailed parsing of **every
  class/struct body** with a bogus "syntax error". Fixed by treating any negative
  `yychar` as empty (`yychar<0`) and clearing with `YYEMPTY` instead of -1.
- **`src/lex.C`** — the `rt()` YYSTYPE helpers zero the union before writing a
  scalar member (LP64: pointer members are 8 bytes, `y.t`/`y.l` write only 4).
- **`src/alloc.C`** — node-backing `chunk()` uses `calloc` instead of `malloc`.
- **`incl-master/incl-linux32/fcntl.h`** — `struct flock` guarded under
  `__CYGWIN__` (Cygwin's `<sys/types.h>` already defines it).
- **`CC3` (the driver)** — compiles cfront's generated (pre-ANSI/K&R) C with
  `gcc -w -std=gnu89 -fno-builtin`, so modern gcc accepts implicit-int / implicit
  declarations.

## Status

- `cfront` **builds**, **translates C++ → C** (classes, virtual functions,
  overloading, references, default args), and the result **compiles, links, and
  runs**. Demo: `demo/shapes.C` (a `Shape`/`Circle`/`Square` hierarchy with
  virtual dispatch) → prints `circle area = 12.5664` / `square area = 9`.
- One-shot driver: **`cfront.ps1`** (PowerShell) / **`cfront-run.sh`** — builds
  everything if needed, shows the generated C (vtables and all), then compiles and
  runs the program.

### Runtime library note

`libC.a` here is a **minimal** runtime (`_main`, `operator new`/`delete`, vector
helpers) — enough for programs that don't use static constructors or `<iostream>`.
Building the full AT&T stream/complex/task library (`03-MAKE-libC.sh`) is a
separate, larger step.
