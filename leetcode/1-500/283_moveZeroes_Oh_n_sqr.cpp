// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        if(nums.size() <= 1) return;
        
        int n1p=0;
        
        while (n1p < nums.size()) {
            if (nums[n1p] == 0) {
                int n2p=n1p;
                while (n2p < nums.size() && nums[n2p] == 0 ) n2p++;
                if (n2p == nums.size()) {
                    n1p = nums.size();
                } else {
                    std::swap(nums[n1p], nums[n2p]);
                    n1p++;
                }
            } else {
                n1p++;
            }
        }
    }
};
