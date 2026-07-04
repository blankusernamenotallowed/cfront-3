#include <stdio.h>
int main(){
  printf("long=%d ptr=%d longlong=%d int=%d short=%d\n",
    (int)sizeof(long),(int)sizeof(void*),(int)sizeof(long long),
    (int)sizeof(int),(int)sizeof(short));
  return 0;
}
