//原先解法:

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> ans;
        ans.reserve(nums.size());
        int h = nums[0];
        ans.push_back(nums[0]);
        for(int i = 1; i < nums.size(); i++){
            h += nums[i];
            ans.push_back(h);
        }
        return ans;
    }
};

//更好解法:

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        for(int i = 1; i < nums.size(); i++){
           nums[i] += nums[i-1];
        }
        return nums;
    }
};

//STL解法

#include <numeric>

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        // 參數：(起點, 終點, 寫入位置)
        // 這裡寫入位置設為 nums.begin()，即為原地修改
        std::partial_sum(nums.begin(), nums.end(), nums.begin());
        return nums;
    }
};

