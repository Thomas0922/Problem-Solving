int singleNumber(int* nums, int numsSize) {
    if(numsSize < 2)return nums[0];
    int result = 0;
   for (int i = 0; i < numsSize; i++) {
        result ^= nums[i];
    }
    return result;
}

