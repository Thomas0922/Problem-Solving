
struct ListNode* mergeTwo(struct ListNode* a, struct ListNode* b) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    while (a && b) {
        if (a->val < b->val) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

struct ListNode* mergeRange(struct ListNode** lists, int left, int right) {
    if (left > right) return NULL;
    if (left == right) return lists[left];

    int mid = left + (right - left) / 2;
    struct ListNode* l1 = mergeRange(lists, left, mid);
    struct ListNode* l2 = mergeRange(lists, mid + 1, right);
    return mergeTwo(l1, l2);
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    return mergeRange(lists, 0, listsSize - 1);
}
