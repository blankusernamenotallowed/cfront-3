#include <stdio.h>
#include <stdlib.h>
int main(){ char*p=getenv("FOOBAR"); printf("FOOBAR=%s\n", p?p:"(null)"); return 0; }
