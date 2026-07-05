#include <stdio.h>
class Adder { int base; public: Adder(int b){ base=b; } int operator()(int x){ return base+x; } };
main(){ Adder add5(5); printf("%d\n", add5(3)); return 0; }
