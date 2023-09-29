// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size(); 
        int check=1, copy=0;
        for (; check < nums.size(); check++) {
            if ((nums[check] == nums[copy]) && !(copy == 0 || nums[copy-1] != nums[copy])) continue;
            nums[++copy] = nums[check];
        }
        return (copy+1);
    }
};
