#include <stdio.h>
class Counter {
    int n;
public:
    Counter() { n = 0; }
    void inc(int by) { n += by; }
    int get() { return n; }
};
main() {
    Counter c;
    c.inc(3); c.inc(4);
    printf("count=%d\n", c.get());
    return 0;
}
