/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    // ===== Step 1: 計算總子集合數量 =====
    int totalsubset = 1 << numsSize;
    // ===== Step 2: 分配記憶體 =====
    int **result = malloc(totalsubset * sizeof(int*));
    *returnColumnSizes = malloc(totalsubset * sizeof(int));
    *returnSize = totalsubset;
    // ===== Step 3: 用每個數字表示一個子集合 =====
    for(int i = 0; i < totalsubset; i++){
        int count = 0;
        for(int j = 0; j < numsSize; j++){
            if(i & (1 << j)){
                count++;
            }
        }
    // 分配這個子集合的記憶體
    result[i] = malloc(count * sizeof(int));
    (*returnColumnSizes)[i] = count;
    // 填入元素
    int idx = 0;
    for(int j = 0; j < numsSize; j++){
        if(i & (1 << j)){
            result[i][idx++] = nums[j]; 
        }
    }
    }
    return result;
}
