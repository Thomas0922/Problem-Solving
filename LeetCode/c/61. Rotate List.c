struct ListNode* rotateRight(struct ListNode* head, int k) {
    // 邊界處理
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }
    
    // 步驟 1：計算長度並找到尾節點
    struct ListNode* tail = head;
    int n = 1;
    while (tail->next != NULL) {
        tail = tail->next;
        n++;
    }
    
    // 步驟 2：優化 k
    k = k % n;
    if (k == 0) {
        return head;  // 不需要旋轉
    }
    
    // 步驟 3：找到新的尾節點（第 n-k 個節點）
    struct ListNode* newTail = head;
    for (int i = 1; i < n - k; i++) {
        newTail = newTail->next;
    }
    
    // 步驟 4：新的頭節點
    struct ListNode* newHead = newTail->next;
    
    // 步驟 5：重新連接
    tail->next = head;      // 原尾連接原頭
    newTail->next = NULL;   // 新尾斷開
    
    return newHead;
}
