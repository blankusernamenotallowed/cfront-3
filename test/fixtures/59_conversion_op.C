#include <stdio.h>
class Cel { double t; public: Cel(double c){ t=c; } operator int(){ return (int)t; } };
main(){ Cel c(36.6); int i = c; printf("%d\n", i); return 0; }
