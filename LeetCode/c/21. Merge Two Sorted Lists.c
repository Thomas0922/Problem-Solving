

/*
原先想法先合併在做排序，但複雜度可能到O(nlogn)，所以換作法


struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;
    struct ListNode* head = list1;
    while(list1->next != NULL){
        list1 = list1->next;
    }
    list1->next = list2;
    int swapped = 1;  
    struct ListNode* ptr;
    int temp;
    while(swapped){
        swapped=0;
        ptr=head;
        while(ptr->next != NULL){
            if(ptr->next->val < ptr->val){
                temp = ptr->val;
                ptr->val = ptr->next->val;
                ptr->next->val = temp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
    }

    return head;
}

*/

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    
    while (list1 && list2) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    
     if(list1 != NULL){
        tail->next = list1;
     }else{
        tail->next = list2;
     }
    
    return dummy.next;
}