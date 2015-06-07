// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// O(n) time and O(n) space
// note that since I only look at last 2 array entries, 
// this solution can be easily optimized to O(1) space
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        
        //dynamic programming cache; money made by robbing *optimal choices* of houses until index i
        vector<int> money(nums.size(), 0);
        money[0] = nums[0];
        money[1] = nums[0] > nums[1] ? nums[0] : nums[1];
        
        //dynamic programming loop
        for (int i=2; i<nums.size(); i++) {
            money[i] = max(nums[i] + money[i-2], money[i-1]);
        }
        return money[nums.size()-1];
    }
};
