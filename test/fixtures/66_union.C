#include <stdio.h>
union U { int i; char c[4]; };
main(){ union U u; u.i = 0x41424344; printf("%c%c\n", u.c[0], u.c[3]); return 0; }
