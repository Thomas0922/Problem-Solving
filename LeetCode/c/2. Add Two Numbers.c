/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* ans = &dummy;

    int carry = 0;
    while(l1 || l2 || carry){
        int val1 = 0, val2 = 0, sum = 0;
        val1 = (l1) ? l1 -> val : 0;
        val2 = (l2) ? l2 -> val : 0;
        sum = val1 + val2 + carry;
        carry = sum / 10;
        int digit = sum % 10;

        struct ListNode* new = (struct ListNode*)malloc(sizeof(struct ListNode));
        new -> val = digit;
        new -> next =NULL;

        ans -> next = new;
        ans = ans -> next;

        if(l1) l1 = l1 -> next;
        if(l2) l2 = l2 -> next;
    }
    return dummy.next;
}
