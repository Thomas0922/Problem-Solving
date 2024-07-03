#include<stdio.h>
#include<malloc.h>

/*直觀想法

int maxProfit(int* prices, int pricesSize) {
    //if (pricesSize < 2) return 0; 
    
    int minPrice = prices[0];
    int maxProfit = 0;
    
    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] < minPrice) {
            minPrice = prices[i];
        } else {
            int currentProfit = prices[i] - minPrice;
            if (currentProfit > maxProfit) {
                maxProfit = currentProfit;
            }
        }
    }
    
    return maxProfit;
}

*/

//sliding windows method

int maxProfit(int* prices, int pricesSize) {
    int left=0,right=1;
    int profit = 0,maxprofit=0;
    while(right<pricesSize){      
        if(prices[left]<prices[right]){
            profit = prices[right] - prices[left];
            maxprofit = (maxprofit<profit)?profit:maxprofit;
        }
        else{left = right;}

        right++;
    }
    return maxprofit;
}



int main(){
   int pricesSize;
   scanf("%d",&pricesSize);
   int *prices = (int*)malloc(pricesSize * sizeof(int));
   for(int i=0;i<pricesSize;i++){
    scanf("%d",&prices[i]);
   }
   if(maxProfit(prices,pricesSize))printf("%d\n5",maxProfit(prices,pricesSize));
   else printf("0\n");
   free(prices);
   return 0;

}