#include <stdio.h>
main(){ try { throw 42; } catch(int e) { printf("caught %d\n", e); } return 0; }
