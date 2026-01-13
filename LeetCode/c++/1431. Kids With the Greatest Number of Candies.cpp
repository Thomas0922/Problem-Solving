//原始解法:

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int max = candies[0];
        vector<bool> result(candies.size());
        for(int i =0 ; i < candies.size(); i++){
            if(max <= candies[i])max = candies[i];
        }
        for(int j : candies){
            result.push_back((extraCandies + j) >= max);
        }
         return result;
    }
};

更佳解法:

#include <algorithm>

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int maxCandies = *max_element(candies.begin(), candies.end());
        
        // 直接建立指定大小的陣列，避免 push_back 開銷
        vector<bool> result(candies.size());
        
        for (int i = 0; i < candies.size(); i++) {
            result[i] = candies[i] + extraCandies >= maxCandies;
        }
        
        return result;
    }
};
