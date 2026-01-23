int findComplement(int num) {
    int mask = 0;
    int temp = num;
    
    // 同時計算位元數和建立 mask
    while (temp > 0) {
        mask = (mask << 1) | 1;  // mask 左移並加 1
        temp >>= 1;              // 處理下一位
    }
    
    return mask ^ num;
}
