/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverse(struct ListNode* head){
    struct ListNode* prev = NULL;
    struct ListNode* cun = head;
    struct ListNode* nex =NULL;
    while(cun){
        nex = cun -> next;
        cun -> next = prev;
        prev = cun;
        cun = nex;
    }
    return prev;
}

bool isPalindrome(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while(fast && fast -> next){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    struct ListNode* secondHalf = reverse(slow);
    
    // 步驟 3：比較前後兩部分
    struct ListNode* p1 = head;
    struct ListNode* p2 = secondHalf;
    
    while (p2) {  // 後半部分可能更短
        if (p1->val != p2->val) {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    
    // 可選：恢復鏈表（如果需要）
    // reverse(secondHalf);
    
    return true;
}
