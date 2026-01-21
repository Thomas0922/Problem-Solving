int hammingDistance(int x, int y) {
    int xor_result = x ^ y;  // 找出不同的位
    int count = 0;
    
    // Brian Kernighan 算法（191 題的方法三）
    while (xor_result) {
        xor_result = xor_result & (xor_result - 1);  // 消除一個 '1'
        count++;
    }
    
    return count;
}
