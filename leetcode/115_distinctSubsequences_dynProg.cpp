// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// O(mn) space and O(mn) time
class Solution {
public:
    int numDistinct(string s, string t) {
        //dynamic programming cache
        vector<vector<int>> cache(s.length()+1, vector<int>(t.length()+1, 0));
        
        //base cases
        cache[0][0] = 1;                             //all s and t letters lined up perfectly w/ this recursion
        for (int i=1; i<s.length(); i++) cache[i][0] = 1;  //some s letters were left, but all t letters consumed. Delete all s letters.
        for (int i=1; i<t.length(); i++) cache[0][i] = 0;  //some t letters left over. This is invalid
        
        for (int si = 1; si <= s.length(); si++) {
            for (int ti = 1; ti <= t.length(); ti++) {
                int cand1 = (s[si-1] == t[ti-1]) ? cache[si-1][ti-1] : 0; //matched this letter in s and t, try prev ones!
                int cand2 = cache[si-1][ti];                              //delete this letter in s, and keep trying to match
                cache[si][ti] = cand1 + cand2;
            }
        }
        return cache[s.length()][t.length()];
    }
};
