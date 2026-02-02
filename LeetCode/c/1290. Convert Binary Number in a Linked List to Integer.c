/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
int getDecimalValue(struct ListNode* head) {
    int ans = 0;
    while(head){
        ans <<= 1;
        if(head -> val){
            ans |= 1;
        }
        head = head -> next;
    
    }
    return ans;
}
