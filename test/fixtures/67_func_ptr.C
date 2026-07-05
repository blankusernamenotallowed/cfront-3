#include <stdio.h>
int add(int a,int b){ return a+b; }
int mul(int a,int b){ return a*b; }
main(){ int (*f)(int,int) = add; printf("%d ", f(3,4)); f = mul; printf("%d\n", f(3,4)); return 0; }
