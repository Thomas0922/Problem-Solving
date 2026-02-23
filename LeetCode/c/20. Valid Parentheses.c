// link list解法

#include<stdio.h>
#include <stdlib.h>

typedef struct Node{
    char data;
    struct Node* next;
}Node;

typedef struct {
    Node* top;
}stack;

void push(stack *st, char s){
    Node* new = (Node*)malloc(sizeof(Node));
    new -> data = s;
    new -> next = st -> top;
    st -> top = new; 
}

char pop(stack *st){
    Node* temp = st -> top;
    char dt = temp -> data;
    st -> top = temp -> next;
    free(temp);
    return dt;
}

bool isValid(char* s) {
   stack* st = (stack*)malloc(sizeof(stack));
   st -> top = NULL;
   
    for(int i = 0; s[i] != '\0'; i++){
        if(s[i] == '(' || s[i] == '{' || s[i] == '['){
            push(st , s[i]);
        }else if(s[i] == ')'){
            if(st -> top == NULL) return false;
            char dt = pop(st);
            if(dt != '(')return false;
        }else if(s[i] == '}'){
            if(st -> top == NULL) return false;
            char dt = pop(st);
            if(dt != '{')return false;
        }else if(s[i] == ']'){
            if(st -> top == NULL) return false;
            char dt = pop(st);
            if(dt != '[')return false;
        }
    }
    return st->top == NULL;
}


//array解法

bool isValid(char* s) {
    char stack[10000];
    int top = -1;
    
    for (int i = 0; s[i]; i++) {
        // 左括號：push 對應的右括號
        if (s[i] == '(') stack[++top] = ')';
        else if (s[i] == '{') stack[++top] = '}';
        else if (s[i] == '[') stack[++top] = ']';
        // 右括號：檢查
        else if (top == -1 || stack[top--] != s[i]) {
            return false;
        }
    }
    
    return top == -1;
}
