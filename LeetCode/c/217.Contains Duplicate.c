#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

bool containsDuplicate(int* nums, int numsSize) {
    int i;
    qsort(nums,numsSize,sizeof(int),cmp);
    if (numsSize < 2){
        return false;
    }
    for(i=0;i<numsSize-1;i++){
      if(nums[i]==nums[i+1])return true;
    }
    return false;
}

int main(int argc,char*argv){
  int nums[] = {1,2,3,1};
  int n = sizeof(nums) / sizeof(nums[0]);
  if(containsDuplicate(nums,n))printf("true\n");
  else printf("false\n");
  return 0;
}