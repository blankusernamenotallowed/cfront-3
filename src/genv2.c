#include <stdio.h>
#include <stdlib.h>
int main(){
 printf("SYSTEMROOT=%s\n", getenv("SYSTEMROOT")?"seen":"(null)");
 printf("PATH=%s\n", getenv("PATH")?"seen":"(null)");
 printf("FOOBAR=%s\n", getenv("FOOBAR")?"seen":"(null)");
 return 0;
}
