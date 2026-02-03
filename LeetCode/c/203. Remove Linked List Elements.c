/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode Dummy;
    Dummy.next = NULL;
    struct ListNode* cun = &Dummy;
    cun -> next = head;

    while(cun && cun -> next){
        if(cun -> next -> val == val){
            struct ListNode* temp = cun -> next;
            cun -> next = cun -> next -> next;
            free(temp);
        }else{
            cun = cun -> next;
        }
    }return Dummy.next;
}
