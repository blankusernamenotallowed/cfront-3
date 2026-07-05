#include <stdio.h>
class A { public: int a(){ return 1; } };
class B { public: int b(){ return 2; } };
class C : public A, public B { public: int c(){ return 3; } };
main(){ C obj; printf("%d %d %d\n", obj.a(), obj.b(), obj.c()); return 0; }
