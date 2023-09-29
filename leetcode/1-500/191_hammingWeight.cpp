// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int hammingWeight(uint32_t n) {
        uint32_t mask = 0x1;
        int wt=0;
        while (mask) {
            wt = (mask & n) ? wt + 1 : wt;
            mask <<= 1;
        }
        return wt;
    }
};
