/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prev = &dummy;

    for(int i = 1; i < left; i++){
        prev = prev -> next;
    }

    struct ListNode* start = prev -> next;
    struct ListNode* then = start -> next;

    while(left < right){
        start -> next = then -> next;
        then -> next = prev -> next;
        prev -> next = then;
        then = start -> next;
        left++;
    }

    return dummy.next;
}
