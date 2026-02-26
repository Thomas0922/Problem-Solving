typedef struct Node {
    int val;
    struct Node* next;
    struct Node* prev;  // ⭐ 雙向
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
    int capacity;
} MyCircularDeque;

// InsertFront：O(1)
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if(obj->size == obj->capacity) return false;
    Node* new = malloc(sizeof(Node));
    new->val = value;
    
    if(obj->size == 0){
        new->next = new;
        new->prev = new;  // 雙向循環
        obj->front = obj->rear = new;
    }else{
        new->next = obj->front;
        new->prev = obj->rear;
        obj->front->prev = new;
        obj->rear->next = new;
        obj->front = new;
    }
    
    obj->size++;
    return true;
}

// InsertLast：O(1)
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if(obj->size == obj->capacity) return false;
    Node* new = malloc(sizeof(Node));
    new->val = value;
    
    if(obj->size == 0){
        new->next = new;
        new->prev = new;
        obj->front = obj->rear = new;
    }else{
        new->prev = obj->rear;
        new->next = obj->front;
        obj->rear->next = new;
        obj->front->prev = new;
        obj->rear = new;
    }
    
    obj->size++;
    return true;
}

// DeleteFront：O(1)
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    if(obj->size == 0) return false;
    Node* temp = obj->front;
    
    if(obj->size == 1){
        obj->front = obj->rear = NULL;
    }else{
        obj->front = temp->next;
        obj->front->prev = obj->rear;
        obj->rear->next = obj->front;
    }
    
    free(temp);
    obj->size--;
    return true;
}

// DeleteLast：O(1) ⭐⭐⭐
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    if(obj->size == 0) return false;
    Node* temp = obj->rear;
    
    if(obj->size == 1){
        obj->front = obj->rear = NULL;
    }else{
        obj->rear = temp->prev;  // ⭐ 直接訪問前驅！
        obj->rear->next = obj->front;
        obj->front->prev = obj->rear;
    }
    
    free(temp);
    obj->size--;
    return true;
}
