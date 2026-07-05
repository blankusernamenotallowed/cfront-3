#include <stdio.h>
template<class T> T maxof(T a, T b){ return a>b?a:b; }
main(){ printf("%d %g\n", maxof(3,7), maxof(2.5,1.5)); return 0; }
