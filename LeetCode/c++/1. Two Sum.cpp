//原本解法

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans = {};
        for(int i = 0; i < nums.size(); i++){
            for(int j = i; j < nums.size(); j++){  // ⚠️ 應從 i+1 開始
                if((nums[i] + nums[j]) == target && (i != j)){
                    ans.push_back(i);
                    ans.push_back(j);
                }   
            }
        }
        return ans;
    }
};

//最佳解法

#include <unordered_map>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 邊界條件：陣列太小
        if (nums.size() < 2) {
            return {};  // 無解
        }
        
        // 哈希表：<數值, 索引>
        unordered_map<int, int> seen;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            // 檢查互補數是否已存在
            if (seen.find(complement) != seen.end()) {
                return {seen[complement], i};
            }
            
            // 將當前數字存入哈希表
            seen[nums[i]] = i;
        }
        
        // 理論上不會執行（題目保證有解）
        return {};
    }
};
