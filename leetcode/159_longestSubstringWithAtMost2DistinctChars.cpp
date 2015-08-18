// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    int maxlen = 1;

public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        if (s.length() == 0) return 0;
        
        char c1=s[0], c2=s[0];
        int c1f = 1, c2f = 1;
        int lhsp=0;     //denotes start of valid substring w/ at most 2 distinct characters
        for (int i=1; i<s.length(); i++) {
            if (s[i] == c1 && s[i] == c2) {
                c1f++; c2f++;
            } else if (s[i] == c1) {
                c1f++;
            } else if (s[i] == c2) {
                c2f++;
            } else if (c1 == c2) {
                c2f = 1;
                c2 = s[i];
            } else {
                while (c1f > 0 && c2f > 0) {
                    if (c1 == s[lhsp]) { c1f--; } 
                    if (c2 == s[lhsp]) { c2f--; }
                    lhsp++;
                }
                if (c1f == 0) { c1 = s[i]; c1f = 1;}
                if (c2f == 0) { c2 = s[i]; c2f = 1;}
            }
            if ((i - lhsp + 1) > maxlen) {
                maxlen = i - lhsp + 1;
            }
        }
        return maxlen;
    }
};
