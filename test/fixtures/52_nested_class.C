#include <stdio.h>
class Outer { public: class Inner { public: int v(){ return 5; } }; };
main(){ Outer::Inner i; printf("%d\n", i.v()); return 0; }
