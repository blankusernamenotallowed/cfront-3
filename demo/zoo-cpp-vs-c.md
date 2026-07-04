0# C++ → C, as done by cfront 3.0.3

This document shows a single C++ source file and the C that **cfront** (the
original 1985 C++ "compiler", which is really a C++→C translator) produces from
it. cfront is how C++ was implemented before native compilers existed: it lowers
classes, inheritance, virtual functions, constructors/destructors and operator
overloading into plain C, which a C compiler then builds.

Generated with:

```sh
./CC -Fc demo/zoo.C      # -Fc = translate to C, keep the .c
```

Program output (after compiling the generated C and running it):

```
A dog  has 4 legs and says 'woof'
A bird has 2 legs and says 'tweet'
a+b = (4, 6)   a.b = 11
```

---

## The C++ source (`demo/zoo.C`)

```cpp
#include <stdio.h>

// ---- a class hierarchy with virtual functions ----
class Animal {
protected:
    int legs;
public:
    Animal(int l)          { legs = l; }
    virtual ~Animal()      {}
    virtual const char* sound() { return "..."; }
    virtual const char* kind()  { return "animal"; }
    void introduce() {                       // non-virtual, calls virtuals
        printf("A %-4s has %d legs and says '%s'\n", kind(), legs, sound());
    }
};

class Dog : public Animal {
public:
    Dog() : Animal(4) {}                     // base-class init
    const char* sound() { return "woof"; }
    const char* kind()  { return "dog"; }
};

class Bird : public Animal {
public:
    Bird() : Animal(2) {}
    const char* sound() { return "tweet"; }
    const char* kind()  { return "bird"; }
};

// ---- operator overloading + default args ----
class Vec2 {
public:
    double x, y;
    Vec2(double a = 0, double b = 0) { x = a; y = b; }
    Vec2 operator+(Vec2 v) { return Vec2(x + v.x, y + v.y); }
    double dot(Vec2& v)    { return x * v.x + y * v.y; }
};

main()
{
    Animal* zoo[2];
    zoo[0] = new Dog;
    zoo[1] = new Bird;
    for (int i = 0; i < 2; i++)
        zoo[i]->introduce();                 // virtual dispatch

    Vec2 a(1, 2), b(3, 4);
    Vec2 c = a + b;                          // operator+
    printf("a+b = (%g, %g)   a.b = %g\n", c.x, c.y, a.dot(b));
    return 0;
}
```

---

## The key transformations

### 1. A class becomes a `struct`; the vtable pointer is an added field

```c
struct Animal {              /* sizeof Animal == 16 */
    int            legs__6Animal;
    struct __mptr *__vptr__6Animal;   /* pointer to the virtual table */
};
```

Every member gets a **mangled name** encoding its class (`legs__6Animal` =
`legs` in the 6-char class `Animal`). Because `Animal` has virtual functions,
cfront injects a hidden `__vptr` field.

### 2. Inheritance = embedding the base layout

A `Dog` *is an* `Animal`, so its struct starts with exactly the `Animal` fields:

```c
struct Dog {                 /* sizeof Dog == 16 */
    int            legs__6Animal;
    struct __mptr *__vptr__6Animal;
};
```

A `Dog*` can therefore be used wherever an `Animal*` is expected — the first
bytes are laid out identically.

### 3. Member functions become free functions with an explicit `this`

```c
static const char *sound__3DogFv (struct Dog *__0this){ return "woof"; }
static const char *kind__6AnimalFv(struct Animal *__0this){ return "animal"; }
```

The name `sound__3DogFv` = method `sound`, class `Dog`, taking `void`. The
implicit `this` becomes an ordinary first parameter, `__0this`.

### 4. Virtual functions become a table of function pointers

Each class gets a `__mptr[]` vtable. An entry is `{short d; short i; __vptp f;}`
— `f` is the function pointer and `d` is the `this`-adjustment (for multiple
inheritance). Slot 1 is the destructor, slot 2 is `sound`, slot 3 is `kind`:

```c
struct __mptr __vtbl__3Dog__demo_zoo_C[] = {
    0,0,0,                                  /* [0] */
    0,0,(__vptp)__dt__3DogFv,               /* [1] destructor */
    0,0,(__vptp)sound__3DogFv,              /* [2] sound()    */
    0,0,(__vptp)kind__3DogFv,               /* [3] kind()     */
    0,0,0 };
```

`zoo[i]->introduce()` calls the virtuals `kind()` and `sound()` **indirectly
through the vtable**, so a `Dog` and a `Bird` behind the same `Animal*` run
different code:

```c
/* kind() :  (*vptr[3].f)( this + vptr[3].d ) */
(*(const char*(*)(struct Animal*))
    ( zoo[i]->__vptr__6Animal[3].f ))
    ( (struct Animal*)((char*)zoo[i] + zoo[i]->__vptr__6Animal[3].d) )
```

That indirect call *is* polymorphism.

### 5. `new Dog` — allocate, then run the constructor chain

`new Dog` becomes: call `operator new` (`__nw__FUl`) for `sizeof(struct Dog)`,
install the `Dog` vtable, run the base `Animal(4)` constructor (which installs
the `Animal` vtable and sets `legs = 4`), then re-install the `Dog` vtable:

```c
zoo[0] = __nw__FUl(sizeof(struct Dog));
      /* base ctor: */ __0__X3->__vptr__6Animal = __ptbl_vec__demo_zoo_C_[0]; /* Animal vtbl */
                       __0__X3->legs__6Animal   = 4;
      /* derived:  */  __0__X9->__vptr__6Animal = __ptbl_vec__demo_zoo_C_[1]; /* Dog vtbl   */
```

`__ptbl_vec__demo_zoo_C_[]` is the per-file table of all vtables:

```c
struct __mptr* __ptbl_vec__demo_zoo_C_[] = {
    __vtbl__6Animal__demo_zoo_C,   /* [0] */
    __vtbl__3Dog__demo_zoo_C,      /* [1] */
    __vtbl__4Bird__demo_zoo_C,     /* [2] */
};
```

### 6. The `virtual ~Animal()` destructor

Destructors become `__dt__…` functions taking a `__0__free` flag: they reset the
vtable pointer and, if the object was heap-allocated, call `operator delete`
(`__dl__FPv`):

```c
static void __dt__3DogFv(struct Dog *__0this, int __0__free){
    if (__0this){
        __0this->__vptr__6Animal = __ptbl_vec__demo_zoo_C_[1];
        ...                                   /* run base ~Animal() */
        if (__0__free & 1) __dl__FPv(__0this);
    }
}
```

### 7. Operator overloading + return-by-value

`a + b` is just a call to the mangled operator function, and returning a `Vec2`
by value is done through a hidden temporary (cfront materialises the result in a
caller-provided slot rather than "returning a struct"):

```cpp
Vec2 c = a + b;               // C++
```
```c
/* C: build the sum in a temp, then copy into c */
__2__X7 = a.x + b.x;
__2__X8 = a.y + b.y;
c.x__4Vec2 = __2__X7;
c.y__4Vec2 = __2__X8;
```

The `Vec2(double a = 0, double b = 0)` **default arguments** are filled in at the
call site, and `dot(Vec2&)` shows a **reference** lowered to a pointer.

---

## The full generated C

For completeness, the entire output of `./CC -Fc demo/zoo.C` (with the `#line`
directives stripped for readability) is in
[`demo/zoo_transpiled.c`](zoo_transpiled.c). The essential structure:

- forward `struct` decls + the `__mptr` vtable-entry type,
- one `struct` per class (with the injected `__vptr`),
- `main()` with all constructor/virtual-call machinery expanded inline,
- the `__dt__…`, `sound__…`, `kind__…` method bodies,
- the per-class `__vtbl__…[]` tables and the `__ptbl_vec__…[]` registry.
