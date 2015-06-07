// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        for (unsigned int i=0; i<nums.size(); i++) {
            bool evalPrev = (i == 0)                 || (nums[i] > nums[i-1]);
            bool evalNext = (i == (nums.size() - 1)) || (nums[i] > nums[i+1]);
            if (evalPrev && evalNext) return i;
        }
        return -1; //not defined or found
    }
};
