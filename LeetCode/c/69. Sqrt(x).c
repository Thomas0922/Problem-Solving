int mySqrt(int x) {
    // 處理特例：0 的平方根是 0，1 的平方根是 1
    if (x == 0 || x == 1) return x;
    
    int left = 1, right = x;
    int ans = 0;
    
    while (left <= right) {
        // 技巧 1：計算中間值。
        // 不寫 (left + right) / 2 是為了避免 left + right 本身就發生整數溢位
        int mid = left + (right - left) / 2;
        
        // 技巧 2：判斷 mid 的平方是否小於等於 x。
        // 為了徹底避免 mid * mid 造成溢位，我們將乘法移項變成除法：判斷 mid <= x / mid
        if (mid <= x / mid) {
            ans = mid;       // mid 可能是答案，我們先記錄下來
            left = mid + 1;  // 看看有沒有更大的數字也符合條件，所以往右半邊找
        } else {
            right = mid - 1; // mid 的平方大於 x 了，代表 mid 太大，往左半邊找
        }
    }
    
    return ans;
}
