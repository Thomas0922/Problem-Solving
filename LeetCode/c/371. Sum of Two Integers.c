#include<stdio.h>

int getSum(int a, int b) {
    unsigned int c=0; //因為要避免溢位所以用umsigned
    while(b){
        c = a & b; //先算要進位的數在哪
        a = a ^ b; //算不進位的加法
        b = c << 1; //左移為了下一輪把進位值加進去
    }return a;
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
