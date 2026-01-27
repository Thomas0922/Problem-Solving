int rangeBitwiseAnd(int left, int right) {
    // 不斷消除 right 最右邊的 1
    while (left < right) {
        right &= (right - 1);
    }
    return right;
}
