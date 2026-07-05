#include <stdio.h>
class C { int x; public: C(){ x=9; } int get() const { return x; } };
main(){ C c; printf("%d\n", c.get()); return 0; }
