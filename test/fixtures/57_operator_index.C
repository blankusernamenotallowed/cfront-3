#include <stdio.h>
class Arr { int d[3]; public: Arr(){ d[0]=10; d[1]=20; d[2]=30; } int& operator[](int i){ return d[i]; } };
main(){ Arr a; a[1]=99; printf("%d %d\n", a[0], a[1]); return 0; }
