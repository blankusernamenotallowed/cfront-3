#include <stdio.h>
class C { int secret; public: C(){ secret=99; } friend int reveal(C&); };
int reveal(C& c){ return c.secret; }
main(){ C c; printf("%d\n", reveal(c)); return 0; }
