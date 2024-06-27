/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int n, int* returnSize) {
    int *result = (int*)malloc((n+1) * sizeof(int));
    *returnSize = n+1;
    for(int i=0;i<=n;i++){
        int count = 0;
        int num = i;
        while(num){
         count += num &1;
         num = num>>1;
        }
        result[i] = count;
    }
    
    
    return result;
}
