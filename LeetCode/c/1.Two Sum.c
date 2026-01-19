//原本解法:

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *ans = malloc(2 * sizeof(int));
    if (ans == NULL){
        *returnSize = 0;
        return NULL;
    }
    for(int i = 0; i < numsSize; i++){
        for (int j = i+1; j < numsSize; j++){
            if(nums[i] + nums[j] == target){
                ans[0] = i;
                ans[1] = j;
                *returnSize = 2;
                return ans;
            }
        }
    }
    free(ans);
    *returnSize = 0;
    return NULL;
}

//更佳解法
#define HASH_SIZE 10007

typedef struct{
    int value;
    int key;
    int used;
}HashTable;

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashTable* hash = (HashTable*)calloc(HASH_SIZE , sizeof(HashTable));
    if(hash == NULL){
        *returnSize = 0;
        free(hash);
        return NULL;
    }

    int *ans = (int*)malloc(2 * sizeof(int));
    if(ans == NULL){
        *returnSize = 0;
        free(hash);
        return NULL;
    }

    for(int i = 0; i < numsSize; i++){
        int com = target - nums[i];
        int h = ((com % HASH_SIZE) + HASH_SIZE) % HASH_SIZE;
        int idx = h;
        while(hash[idx].used){
            if(hash[idx].value == com){
                ans[0] = hash[idx].key;
                ans[1] = i;
                *returnSize = 2;
                free(hash);
                return ans;
            }
            idx = (idx + 1) % HASH_SIZE;
        }
        h = ((nums[i] % HASH_SIZE) + HASH_SIZE) % HASH_SIZE;
        idx = h;
        while(hash[idx].used){
            idx = (idx + 1) % HASH_SIZE;
        }
        hash[idx].value = nums[i];
        hash[idx].key = i;
        hash[idx].used = 1;
    }
    *returnSize = 0;
    free(hash);
    free(ans);
    return NULL;
}
