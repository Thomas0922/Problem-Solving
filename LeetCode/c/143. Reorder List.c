/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void reorderList(struct ListNode* head) {

    if (!head || !head->next) return;
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while(fast && fast -> next){
        slow = slow -> next;
        fast = fast -> next -> next;
    }

    struct ListNode* curr = slow -> next;
    slow->next = NULL;
    struct ListNode* prev = NULL;
    while(curr){
        struct ListNode* nex = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = nex;
    }
    struct ListNode* t1 = head;
    struct ListNode* t2 = prev;

    while(t2){
        struct ListNode *p1 = t1->next;
        struct ListNode *p2 = t2->next;
        t1 -> next = t2;
        t2 -> next = p1;

        t1 = p1;
        t2 = p2;
    }
}
