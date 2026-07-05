#include <stdio.h>
class Shape { public: virtual int area()=0; };
class Sq : public Shape { int s; public: Sq(int x){ s=x; } int area(){ return s*s; } };
main(){ Shape* p = new Sq(4); printf("%d\n", p->area()); return 0; }
