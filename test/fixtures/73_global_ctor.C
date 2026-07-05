#include <stdio.h>
class Global {
    int v;
public:
    Global()  { v = 42; printf("ctor\n"); }   // must run BEFORE main
    ~Global() { printf("dtor\n"); }            // must run at exit
    int get() { return v; }
};
Global g;
main() {
    printf("main sees %d\n", g.get());
    return 0;
}
