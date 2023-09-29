// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//O(n^2) dynamic programming is too slow
//other algorithm is O(n)
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() == 0) return false;
        
        //dynamic programming cache
        vector<bool> cache(nums.size(), false);
        cache[nums.size()-1] = true;
        
        //dynamic programming bottom-up loop
        for (int ind=nums.size()-2; ind >= 0; ind--) {
            bool possible = false;
            for (int i=ind; (i<=ind+nums[ind]) && (i<nums.size()) ; i++) {
                if (cache[i]) {
                    possible = true; 
                    break;
                }
            }
            cache[ind] = possible;
        }
        return cache[0];
    }
};
