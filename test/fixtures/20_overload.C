#include <stdio.h>
int    maxv(int a, int b)       { return a > b ? a : b; }
double maxv(double a, double b) { return a > b ? a : b; }
void   bump(int& x, int by = 1) { x += by; }
main() {
    int n = 5;
    bump(n); bump(n, 10);
    printf("n=%d max=%d %g\n", n, maxv(3, 7), maxv(2.5, 1.5));
    return 0;
}
