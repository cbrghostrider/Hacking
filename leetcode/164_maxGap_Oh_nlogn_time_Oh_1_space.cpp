// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        if (nums.size() <= 1) return 0;
        int maxdiff = nums[1] - nums[0];
        for (int i=1; i<nums.size(); i++) {
            int diff = nums[i] - nums[i-1];
            if (diff > maxdiff) maxdiff = diff;
        }
        return maxdiff;
    }
};
