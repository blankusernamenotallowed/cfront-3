#include <stdio.h>
int counter(){ static int n = 0; return ++n; }
main(){ int a=counter(); int b=counter(); int c=counter(); printf("%d %d %d\n", a,b,c); return 0; }
