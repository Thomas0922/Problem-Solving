/*原本最直觀解法但時間複雜度會來到o(logn)，所以改用其他解法

int cmp(const void *a,const void *b){
    return *(int*)a - *(int*)b;
}


int missingNumber(int* nums, int numsSize) {
    qsort(nums,numsSize,sizeof(int),cmp);
    for(int i=0;i<numsSize;i++){
        if(nums[i]!=i)return i;
    }
    return numsSize;
}

*/

int missingNumber(int* nums, int numsSize) {
    int total = numsSize * (numsSize + 1) / 2, miss=0;
    for(int i=0;i<numsSize;i++){
        miss += nums[i];
    }
   return total - miss;
}
