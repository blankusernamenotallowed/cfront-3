#include <stdio.h>
class Global {
public:
    int v;
    Global() { v = 12345; }   // runs before main IF static init works
};
Global g;                     // global object with a constructor
main() {
    printf("g.v = %d\n", g.v);
    return 0;
}
