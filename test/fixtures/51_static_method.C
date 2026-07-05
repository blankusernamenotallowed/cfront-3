#include <stdio.h>
class C { public: static int twice(int x){ return x*2; } };
main(){ printf("%d\n", C::twice(21)); return 0; }
