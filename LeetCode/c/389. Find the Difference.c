char findTheDifference(char* s, char* t) {
    int  ans = 0;
    for(int i = 0; s[i] != '\0'; i++){
        ans ^= s[i] ^ t[i];
    }
    ans ^= t[strlen(s)];
    return (char)ans;
}
