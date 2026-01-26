/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* singleNumber(int* nums, int numsSize, int* returnSize) {
    int *result = (int*)malloc(2 * sizeof(int));
    if (!result) return NULL;
    int xor_result = 0;
    for(int i = 0; i < numsSize; i++){
        xor_result ^= nums[i];
    }

    unsigned int diff = (unsigned int)xor_result & -(unsigned int)xor_result;
    int a = 0, b = 0;
    for(int i = 0; i < numsSize; i++){
        if(nums[i] & diff){
            a ^= nums[i];
        }else{
            b ^= nums[i];
        }
    }
    *returnSize = 2;
    result[0] = a;
    result[1] = b;
    return result;
}
