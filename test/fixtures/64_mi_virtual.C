#include <stdio.h>
class A { public: virtual int who(){ return 1; } };
class B { public: virtual int what(){ return 2; } };
class C : public A, public B { public: int who(){ return 10; } int what(){ return 20; } };
main(){ C obj; A* pa = &obj; B* pb = &obj; printf("%d %d\n", pa->who(), pb->what()); return 0; }
