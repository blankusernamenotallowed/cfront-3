#include <stdio.h>
class P { public: int x,y; P(){ x=0; y=0; } P(int a){ x=a; y=0; } P(int a,int b){ x=a; y=b; } };
main(){ P p1; P p2(5); P p3(3,4); printf("%d %d %d %d %d %d\n", p1.x,p1.y,p2.x,p2.y,p3.x,p3.y); return 0; }
