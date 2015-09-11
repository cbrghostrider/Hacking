// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        for (int i=1; i<nums.size(); i+=2) {
            if (i+1 == nums.size()) break;
            std::swap(nums[i], nums[i+1]);
        }
    }
};
