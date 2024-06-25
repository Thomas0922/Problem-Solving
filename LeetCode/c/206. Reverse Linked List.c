/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    if (!head) return head;
    struct ListNode *Current = head;
    struct ListNode *Next = NULL;
    struct ListNode *Pre = NULL;

    while(Current){
        Next = Current -> next;
        Current -> next = Pre;
        Pre = Current;
        Current = Next;
    }
    return Pre;

    
}