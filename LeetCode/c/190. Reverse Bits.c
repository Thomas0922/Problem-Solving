uint32_t reverseBits(uint32_t n) {
    uint32_t temp=0;
    for(int i=0;i<32;i++){
        temp = (temp<<1) | (n&1);
        n = n>>1;
    }
    return temp;
}
