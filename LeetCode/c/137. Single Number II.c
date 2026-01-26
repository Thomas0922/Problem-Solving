int singleNumber(int* nums, int numsSize) {
    int ones = 0;  // 記錄出現 1 次的位
    int twos = 0;  // 記錄出現 2 次的位
    
    for (int i = 0; i < numsSize; i++) {
        // 更新 twos：之前在 ones 中且當前也是 1 的位
        twos |= ones & nums[i];
        
        // 更新 ones：異或操作
        ones ^= nums[i];
        
        // 清除出現 3 次的位（同時在 ones 和 twos 中）
        int threes = ones & twos;
        ones &= ~threes;
        twos &= ~threes;
    }
    
    return ones;  // 只出現 1 次的數字
}
