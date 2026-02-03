struct ListNode* deleteDuplicates(struct ListNode* head) {
    // 1. 安全檢查：如果 list 是空的或只有一個節點，直接回傳
    if (!head) return NULL;

    struct ListNode* curr = head;

    // 2. 遍歷清單
    while (curr && curr->next) {
        // 如果當前值跟下一個值一樣
        if (curr->val == curr->next->val) {
            // 直接跳過下一個節點
            curr->next = curr->next->next;
            // 注意：這裡不需要移動 curr，因為新的 curr->next 可能還是重複的
        } else {
            // 如果不一樣，才移動指標到下一個節點
            curr = curr->next;
        }
    }

    return head;
}
