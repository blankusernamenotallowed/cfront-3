#include <stdio.h>
class Noisy { int id; public: Noisy(int i){ id=i; printf("ctor %d\n", id); } ~Noisy(){ printf("dtor %d\n", id); } };
main(){ { Noisy a(1); Noisy b(2); } printf("done\n"); return 0; }
