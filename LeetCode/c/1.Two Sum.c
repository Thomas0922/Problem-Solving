#include<stdio.h>
#include<stdlib.h>


int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    for(int i=0;i<numsSize-1;i++){
        for(int j=i+1;j<numsSize;j++){
            if(nums[i]+nums[j] == target){
                result[0]=i;
                result[1]=j;
                return result;
            }
        }
    }
    returnSize=0;
    free(result);
    return NULL;
}

int main(){
  int numsSize,target;
  printf("Input Array size:");
  scanf("%d",&numsSize);

  printf("Input target:");
  scanf("%d",&target);

  int *nums = malloc(numsSize * sizeof(int));

  printf("Input nums:\n");
  for(int i=0;i<numsSize;i++){
    scanf("%d",&nums[i]);
  }

  int returnSize;
  int *result = twoSum(nums,numsSize,target,&returnSize);
  if(result != NULL) {
        printf("Find Index:[%d,%d]\n", result[0], result[1]);
        free(result);
    } else {
        printf("NULL\n");
    }
    free(nums);
    return 0;
}