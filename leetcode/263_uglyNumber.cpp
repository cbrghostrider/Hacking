// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    bool isUgly(int num) {
        if (num == 1) return true;
        if (num <= 0) return false;
        while ((num % 2) == 0) num /= 2;
        while ((num % 3) == 0) num /= 3;
        while ((num % 5) == 0) num /= 5;
        return (num == 1);
    }
};
