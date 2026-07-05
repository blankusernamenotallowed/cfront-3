#include <stdio.h>
class C { public: int v; C(int x){ v=x; } C(const C& o){ v=o.v+100; } };
main(){ C a(5); C b=a; printf("%d\n", b.v); return 0; }
