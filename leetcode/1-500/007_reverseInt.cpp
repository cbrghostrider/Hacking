// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int reverse(int x) {
        bool isNeg = (x < 0);
        long num = isNeg ? x*(-1) : x;
        
        long retAbs=0;
        while (num) {
            retAbs = retAbs*10 + (num % 10);
            num = num / 10;
        }
        
        int ret = retAbs;
        if (ret != retAbs) {
            return 0; //overflow
        }
        
        return (isNeg ? ret * (-1) : ret);
    }
};
