// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// O(mn) runtime, and O(mn) space, where
// m == s1.length() and n == s2.length()
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if ((s1.length() + s2.length()) != s3.length()) return false; 
        
        bool cache[s1.length()+1][s2.length()+1];
        cache[0][0] = true; //everything matched
        
        //compute top row
        for (int s2p=1; s2p<=s2.length(); s2p++) {
            cache[0][s2p] = (s2[s2p-1] == s3[s2p-1]) ? (cache[0][s2p-1]) : false;
        }
        //compute left col
        for (int s1p=1; s1p<=s1.length(); s1p++) {
            cache[s1p][0] = (s1[s1p-1] == s3[s1p-1]) ? (cache[s1p-1][0]) : false;
        }
        //recurrence equation        
        for (int s1p=1; s1p<=s1.length(); s1p++) {
            for (int s2p=1; s2p<=s2.length(); s2p++) {
                if (s1[s1p-1] == s3[s1p+s2p-1] && s2[s2p-1] == s3[s1p+s2p-1]) {
                    cache[s1p][s2p] = cache[s1p-1][s2p] || cache[s1p][s2p-1];
                } else if (s1[s1p-1] == s3[s1p+s2p-1]) {
                    cache[s1p][s2p] = cache[s1p-1][s2p];
                } else if (s2[s2p-1] == s3[s1p+s2p-1]) {
                    cache[s1p][s2p] = cache[s1p][s2p-1];
                } else {
                    cache[s1p][s2p] = false;
                }
            }
        }
        return cache[s1.length()][s2.length()];
    }
};
