// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n1cp=0, n1fp=0;
        while (n1fp < nums.size()) {
            if (nums[n1fp] != val) {
                n1cp++;
                n1fp++;
            } else {
                n1fp++;
                while (n1fp < nums.size() && nums[n1fp] != val) {
                    nums[n1cp++] = nums[n1fp++];
                }
            }
        }
        return n1cp;
    }
};
