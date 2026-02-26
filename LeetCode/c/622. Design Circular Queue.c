
typedef struct Node {
    int val;
    struct Node* next;
} Node;

typedef struct {
    Node* rear;
    Node* front;
    int size;
    int capacity;
} MyCircularQueue;


MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* obj = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    obj -> front = NULL;
    obj -> rear = NULL;
    obj -> size = 0;
    obj -> capacity = k;
    return obj;
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return (obj -> front == NULL);
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if(obj -> size == obj -> capacity){
        return false;
    }

    Node* new = (Node*)malloc(sizeof(Node));
    new -> val = value;
    if(myCircularQueueIsEmpty(obj)){
        new -> next = new;
        obj -> front = obj -> rear = new; 
    }else{
        new -> next = obj -> front;
        obj -> rear -> next = new;
        obj -> rear = new;
    }
    obj->size++;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if(myCircularQueueIsEmpty(obj)){
        return false;
    }

    Node* temp = obj -> front;
    if(obj -> size == 1){
        obj -> front = obj -> rear = NULL;
    }else{
        obj -> front = temp -> next;
        obj -> rear -> next = obj -> front;
    }
    free(temp);
    obj -> size--;
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
    if(myCircularQueueIsEmpty(obj)){
        return - 1;
    }
    return obj -> front -> val;
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if(myCircularQueueIsEmpty(obj)){
        return - 1;
    }
    return obj -> rear -> val;    
}



bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return obj -> size == obj -> capacity;
}

void myCircularQueueFree(MyCircularQueue* obj) {
    while(!myCircularQueueIsEmpty(obj)){
        myCircularQueueDeQueue(obj);
    }free(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 
 * bool param_2 = myCircularQueueDeQueue(obj);
 
 * int param_3 = myCircularQueueFront(obj);
 
 * int param_4 = myCircularQueueRear(obj);
 
 * bool param_5 = myCircularQueueIsEmpty(obj);
 
 * bool param_6 = myCircularQueueIsFull(obj);
 
 * myCircularQueueFree(obj);
*/
