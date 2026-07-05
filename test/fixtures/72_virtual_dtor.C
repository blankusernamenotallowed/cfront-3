#include <stdio.h>
class Base { public: virtual ~Base(){ printf("~Base\n"); } };
class Der : public Base { public: ~Der(){ printf("~Der\n"); } };
main(){ Base* p = new Der; delete p; return 0; }
