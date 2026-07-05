#include <stdio.h>
class C { public: static int count; };
int C::count = 7;
main(){ printf("%d\n", C::count); return 0; }
