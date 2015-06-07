// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() <= 1) return true;
        
        //scan backward till you find 0, then keep accumulating jump distance 
        //and keep scanning until possible to jump (or not)
        int jumpReq = 0;
        for (int ind=nums.size()-2; ind >=0; ind--) {
            if (nums[ind] == 0) {
                jumpReq=1;
                while ((ind >= 0) && (nums[ind] < jumpReq)) {
                    ind--;
                    jumpReq++;
                }
                if (ind < 0) break;
                jumpReq = 0;
            }
        }
        return (jumpReq == 0);
    }
};
