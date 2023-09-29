// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int copy=0, check=0;
        for (int check=0; check<nums.size(); check++) {
            if (nums[check]) {
                std::swap(nums[copy++], nums[check]);
            }
        }
    }
};
