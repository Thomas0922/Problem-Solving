
typedef struct Node{
    int val;
    struct Node* next;
} Node;

typedef struct Queue{
    Node* front;
    Node* rear;
    int size;
} Queue;

Queue* queuecreate(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

bool isempty(Queue* q){
    return (q -> front == NULL);
}

void enqueue(Queue* q, int x){
    Node* new = (Node*)malloc(sizeof(Node));
    new -> val = x;
    new -> next = NULL;
    if(isempty(q)){
        q -> front = q -> rear = new;
    }else{
        q -> rear -> next = new;
        q -> rear = new;
        
    }q->size++;
}

int dequeue(Queue* q){
    Node* temp = q -> front;
    if(isempty(q))return -1;
    q -> front = temp -> next;
    if(q->front == NULL) q->rear = NULL;  // 重要！
    int val = temp -> val;
    free(temp);
    q->size--;
    return val;    
}

int top(Queue* q){
    if(isempty(q))return -1;
    return q -> front -> val;
}

void freequeue(Queue* q){
    while(!isempty(q)){
        dequeue(q);
    }free(q);
}

int queuesize(Queue* q){
    return q->size;
}

typedef struct {
    Queue* q;
} MyStack;


MyStack* myStackCreate() {
    MyStack* obj = (MyStack*)malloc(sizeof(MyStack));
    obj -> q = queuecreate();

    return obj;
}

void myStackPush(MyStack* obj, int x) {
    int n = queuesize(obj -> q);

    enqueue(obj->q, x);

    for(int i = 0; i < n; i++){
        enqueue(obj -> q, dequeue(obj -> q));
    }
}

int myStackPop(MyStack* obj) {
    return dequeue(obj -> q);
}

int myStackTop(MyStack* obj) {
    return top(obj -> q);
}

bool myStackEmpty(MyStack* obj) {
    return isempty(obj -> q);
}

void myStackFree(MyStack* obj) {
    freequeue(obj -> q);
    free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/
