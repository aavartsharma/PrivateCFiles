#include<stdio.h>

int main(void){
  int arr[] = {5,6,7,8};
  int* a = arr;
  printf("%d\n", *a++);
  printf("%d\n", *(a-1));
  printf("%zu %zu\n", sizeof(a),sizeof(arr));
  printf("%zu\n", sizeof(arr)/sizeof(int));
  return 0;

}
