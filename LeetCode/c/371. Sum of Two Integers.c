#include<stdio.h>

int getSum(int a, int b) {
    unsigned int c=0;
    while(b){
        c = a & b;
        a = a ^ b;
        b = c << 1;
    }return a;
}

int main(){
    int a,b;
    while(scanf("%d %d",&a,&b)!=EOF){
    if(getSum(a,b))printf("%d\n",getSum(a,b));
    if(a==0 || b==0)break;
    }
    return 0;
}