// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    string convertToTitle(int n) {
        if (n <= 0) return "";
        if (n < 26) {
            return string (1, n - 1 + 'A');
        } else if ((n % 26) == 0) {
            return (convertToTitle(n/26 - 1) + "Z");
        }
        return (convertToTitle(n/26) + convertToTitle(n%26));
    }
};
