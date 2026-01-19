int removeDuplicates(int* nums, int numsSize) {
    int j = 0;
        //加入邊界檢查
    if (nums == NULL || numsSize == 0) {
        return 0;
    }
    for(int i = 1; i < numsSize; i++){
        if(nums[i] != nums[j]){
            j++;
            nums[j] = nums[i];
        }
    }
    return j+1;

}
