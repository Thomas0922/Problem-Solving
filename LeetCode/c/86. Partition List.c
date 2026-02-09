/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode less_dummy;
    struct ListNode greater_dummy;
    less_dummy.next = NULL;
    greater_dummy.next = NULL;

    struct ListNode *less = &less_dummy;
    struct ListNode *greater = &greater_dummy;
    struct ListNode *list = head;

    while(list){
        if(list -> val < x){
            less -> next = list;
            less = less -> next;
        }else{
            greater -> next = list;
            greater = greater -> next;
        }
        list = list -> next;
    }
    less -> next = greater_dummy.next;
    greater -> next = NULL;

    return less_dummy.next;
}
