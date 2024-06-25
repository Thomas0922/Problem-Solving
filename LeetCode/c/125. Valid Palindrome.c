#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
#include<string.h>

bool isPalindrome(char* s) {
    int n =strlen(s);
    int left = 0;
    int right = n-1;
    while(left<right){
        if(isalnum(s[left]) && isalnum(s[right])){
            if(tolower(s[left])!=tolower(s[right]))return false;
            left++;
            right--;
        } 
        if (!isalnum(s[left])) left++;
        if (!isalnum(s[right])) right--;
       
    }
    return true;
}
    
int main(){
    char s[200000];
    scanf("%[^\n]",s);
    if(isPalindrome(s))printf("true\n");
    else printf("false\n");
    return 0;
}