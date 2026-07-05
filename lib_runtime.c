/* Minimal-but-real cfront runtime for this build.
   Provides the static-init machinery (so GLOBAL constructors run), operator
   new/delete, array new/delete, and the pure-virtual placeholder.
   Built into libC.a and linked by the CC driver. */
#include <stdlib.h>
#include <stdio.h>

typedef int (*PFV)();

/* munch generates a __ctdt.c defining strong _ctors[]/_dtors[]. When a program
   has no static objects, munch emits nothing and the empty defaults come from a
   SEPARATE archive member (lib_defaults.c) — the archive-member pattern, which
   works on PE/COFF where weak-symbol override does not. */
extern PFV _ctors[];
extern PFV _dtors[];

static void _run_dtors(void)
{
    PFV* p;
    for (p = _dtors; *p; ++p) (**p)();
}

/* cfront's translated main() begins with a call to _main(): run the static
   constructors munch collected, and schedule the destructors for exit. */
void _main(void)
{
    PFV* p;
    for (p = _ctors; *p; ++p) (**p)();
    atexit(_run_dtors);
}

void* __nw__FUl(unsigned long n) { return malloc((size_t)n); }   /* operator new    */
void  __dl__FPv(void* p)         { free(p); }                    /* operator delete */

void __pure_virtual_called(void)
{
    fprintf(stderr, "pure virtual called\n");
    abort();
}

/* array new: base (0 => allocate), count, elem size, per-element ctor */
void* __vec_new(void* p, int nelem, int sz, void* ctor)
{
    char* base = p ? (char*)p : (char*)malloc((size_t)nelem * (size_t)sz);
    if (ctor) {
        void* (*f)(void*) = (void* (*)(void*))ctor;
        int i;
        for (i = 0; i < nelem; i++) f(base + (size_t)i * (size_t)sz);
    }
    return base;
}

void __vec_delete(void* p, int nelem, int sz, void* dtor, int freeflag, int ignore)
{
    (void)ignore;
    if (!p) return;
    if (dtor) {
        void (*d)(void*, int) = (void (*)(void*, int))dtor;
        int i;
        for (i = nelem - 1; i >= 0; i--) d((char*)p + (size_t)i * (size_t)sz, 0);
    }
    if (freeflag & 1) free(p);
}
