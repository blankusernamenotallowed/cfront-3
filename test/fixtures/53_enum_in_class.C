#include <stdio.h>
class C { public: enum Color { RED=1, GREEN=2, BLUE=4 }; };
main(){ printf("%d\n", C::RED | C::BLUE); return 0; }
