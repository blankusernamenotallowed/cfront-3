#include <stdio.h>

int    maxv(int a, int b)       { return a > b ? a : b; }
double maxv(double a, double b) { return a > b ? a : b; }   // overloaded

void bump(int& x, int by = 1)   { x += by; }                // reference + default arg

main()
{
    int n = 5;
    bump(n);
    bump(n, 10);
    printf("n = %d\n", n);
    printf("max(3,7)=%d  max(2.5,1.5)=%g\n", maxv(3, 7), maxv(2.5, 1.5));
    return 0;
}
