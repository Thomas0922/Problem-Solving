/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* merge(struct ListNode* list1, struct ListNode* list2){



    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* ans = &dummy;

    while(list1 && list2){
        if(list1 -> val < list2 -> val){
            ans -> next = list1;
            list1 = list1 -> next;
        }else{
            ans -> next = list2;
            list2 = list2 -> next;
        }
        ans = ans -> next;
    }

    if(list1){
        ans -> next = list1;
    }else{
        ans -> next = list2;
    }

    return dummy.next;
}

struct ListNode* sortList(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    struct ListNode* prev = NULL;

    // 遞歸終止條件
    if (!head || !head->next) return head;
    while(fast && fast -> next){
        prev = slow;
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    prev -> next = NULL;

    struct ListNode* left = sortList(head);
    struct ListNode* right = sortList(slow);

    return merge(left , right);
}
