#include <stdio.h>
struct Flags { unsigned a:1; unsigned b:3; unsigned c:4; };
main(){ struct Flags f; f.a=1; f.b=5; f.c=10; printf("%d %d %d\n", f.a, f.b, f.c); return 0; }
