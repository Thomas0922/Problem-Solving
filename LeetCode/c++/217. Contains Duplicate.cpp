//原本解法

#include <unordered_map>

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, int> mp;
        
        for(int i = 0; i < nums.size(); i++){
            mp[nums[i]]++;              // 計數器加1
            if(mp[nums[i]] > 1)        // 發現重複立即返回
                return true;
        }
        return false;
    }
};

//更好解法

#include <unordered_set>

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        
        for (int num : nums) {
            // count() 返回元素數量：0(不存在) 或 1(存在)
            if (seen.count(num)) {
                return true;  // count > 0 表示已存在
            }
            seen.insert(num);
        }
        
        return false;
    }
};
