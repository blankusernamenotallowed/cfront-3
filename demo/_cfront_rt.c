/* Minimal cfront-3 runtime for demos (no static ctors / iostreams). */
#include <stdlib.h>
void  _main(void)              {}
void  __vec_new(void)          {}
void  __vec_delete(void)       {}
void* __nw__FUl(unsigned long n){ return malloc(n); }   /* operator new    */
void  __dl__FPv(void* p)       { free(p); }             /* operator delete */
