#include<stdio.h>

int hammingWeight(int n) {
    
    int res =0;
    while(n){
        int bits = n&1;
        if(bits){
            res++;
        }
        n = n>>1;
    }
    return res;
}

int main(int argc,char *argv[]){
    int input;
    while(scanf("%d",&input)!=EOF){
    if(input == -1)break;
    int result = hammingWeight(input);
     printf("%d\n",result);
     
     
    }
 
    
    return 0;
}
