#include <stdio.h>
class C { public: int v; C(){ v = 7; } };
main(){ C* a = new C[3]; printf("%d %d\n", a[0].v, a[2].v); return 0; }
