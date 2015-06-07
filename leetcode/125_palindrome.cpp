// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    bool isPalindrome(string s) {
        int lhs=0, rhs=s.length()-1;
        while (lhs <= rhs) {
            while (lhs < s.size() && !((s[lhs] >= '0' && s[lhs] <= '9') || (toupper(s[lhs]) >= 'A' && toupper(s[lhs]) <= 'Z'))) {
                lhs++;
            }
            while (rhs >= 0 && !((s[rhs] >= '0' && s[rhs] <= '9') || (toupper(s[rhs]) >= 'A' && toupper(s[rhs]) <= 'Z'))) {
                rhs--;
            }
            if (lhs <= rhs) {
                if (toupper(s[lhs]) == toupper(s[rhs])) {
                    lhs++;
                    rhs--;
                } else {
                    return false;   
                }
            }
        }
        return true;
    }
};
