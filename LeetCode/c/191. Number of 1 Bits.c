//原始解法

int hammingWeight(int n) {
    int count = 0;
    while(n){
        if(n % 2 == 1){
            count++;
        }
        n = n / 2;
    }
    return count;
}

//最佳解法
int hammingWeight(int n) {
    //Brian Kernighan
    int count = 0;
    while(n){
        n = n & (n - 1);
        count++;
    }
    return count;
}
