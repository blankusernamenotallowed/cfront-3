#include <stdio.h>
class V { public: int x,y; V(int a,int b){x=a;y=b;} V operator+(V o){ return V(x+o.x,y+o.y); } };
main(){ V a(1,2), b(3,4); V c=a+b; printf("%d %d\n", c.x, c.y); return 0; }
