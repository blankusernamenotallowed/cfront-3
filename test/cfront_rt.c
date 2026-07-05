/* Minimal cfront runtime, MSVC-compilable, so transpiled test programs link
   into a runnable .exe. Enough for classes/virtuals/new/delete/arrays; no
   static constructors or iostreams. */
#include <stdlib.h>
#include <stdio.h>

void  _main(void)                { }
void* __nw__FUl(unsigned long n) { return malloc((size_t)n); }   /* operator new    */
void  __dl__FPv(void* p)         { free(p); }                    /* operator delete */

/* Abstract-method slot placeholder (referenced by a pure-virtual vtable entry,
   never actually invoked in correct programs). */
void __pure_virtual_called(void) { fprintf(stderr, "pure virtual called\n"); abort(); }

/* Array new/delete: cfront passes base (0 => allocate), count, element size, and
   the per-element ctor  struct X* (*)(struct X* this). */
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

/* dtor: void (*)(void* this, int free_flag); then free the whole block. */
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
