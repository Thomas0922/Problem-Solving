#include<stdio.h>

int getSum(int a, int b) {
    unsigned int ua = a, ub = b;
    while (ub) {
        unsigned int carry = (ua & ub) << 1;
        ua = ua ^ ub;
        ub = carry;
    }
    return (int)ua;
}



//測試程式

int main(){
    int a,b;
    while(scanf("%d %d",&a,&b)!=EOF){
    if(getSum(a,b))printf("%d\n",getSum(a,b));
    if(a==0 || b==0)break;
    }
    return 0;
}
