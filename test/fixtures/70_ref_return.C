#include <stdio.h>
int arr[3] = {1,2,3};
int& at(int i){ return arr[i]; }
main(){ at(1) = 99; printf("%d\n", arr[1]); return 0; }
