
typedef struct Node {
    int value;     
    int min;        // push 時此節點對應的最小值
    struct Node* next;
} Node;

typedef struct {
    Node* top;    
} MinStack;


MinStack* minStackCreate() {
    MinStack* st = (MinStack*)malloc(sizeof(MinStack));
    st->top = NULL;
    return st;
}

void minStackPush(MinStack* obj, int val) {
    Node* new = (Node*)malloc(sizeof(Node));
    new -> value = val;

    // 設定 min 值
    if (obj -> top == NULL) {
        new -> min = val; // 空 stack，min 就是自己
    } else {
        new -> min = val < obj -> top -> min ? val : obj -> top -> min;
    }

    new -> next = obj -> top;
    obj -> top = new;
}

void minStackPop(MinStack* obj) {
    Node* temp = obj -> top;
    obj -> top = temp -> next;
    free(temp);
}

int minStackTop(MinStack* obj) {
    Node* temp = obj -> top;
    int val = temp -> value;
    return val;
}

int minStackGetMin(MinStack* obj) {
    return obj -> top -> min;
}

void minStackFree(MinStack* obj) {
    // 先釋放所有節點
    while (obj->top != NULL) {
        Node* temp = obj->top;
        obj->top = temp->next;
        free(temp);
    }
    // 再釋放棧結構
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
