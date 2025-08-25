#include <stdio.h>
#include<stdlib.h>

int* twoSum(int* nums,int length, int target) {
    for (int i=0; i<length;i++){
        for (int j =i; j < length; j++)
        {
            if(nums[i]+ nums[j] == target)
            {
                int* a = malloc(2*sizeof(int));
                if (!a){
                    printf("this failed");
                    return NULL;
                }
                *a = i;
                
                *(a+1) =j;
                return a;
            }
        }
    }
    return NULL;
}

int main(void)
{
  int d[3] = {3,2,4};
  int* result = twoSum(d,sizeof(d)/sizeof(d[0]),6);
  if(!result){
    printf("result is not write\n");
    return 1;
  }
  for(int i=0; i < 2; i++){
    printf("%d\n",result[i]);
  }
  return 0;
}
