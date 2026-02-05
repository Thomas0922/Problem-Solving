struct ListNode* swapPairs(struct ListNode* head) {
    // 邊界情況：空鏈表或只有一個節點
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // 創建 dummy node
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prev = &dummy;

    // 遍歷鏈表，兩兩交換
    while (prev->next && prev->next->next) {
        // 獲取要交換的兩個節點
        struct ListNode* slow = prev->next;      // 第一個節點
        struct ListNode* fast = prev->next->next; // 第二個節點

        // 交換操作（三步）
        slow->next = fast->next;  // 步驟 1
        fast->next = slow;        // 步驟 2
        prev->next = fast;        // 步驟 3

        // 移動到下一組
        prev = slow;
    }

    return dummy.next;
}
