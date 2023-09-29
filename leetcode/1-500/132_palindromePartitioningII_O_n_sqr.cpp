// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    vector<vector<bool>> bcache;
    bool isPalindrome_(int from, int to) { return (bcache[from][to]); }
public:
    int minCut(string s) {
        if (s.length() == 0) return 0;
        bcache = vector<vector<bool>>(s.length(), vector<bool>(s.length(), false));
        for (int ft=0; ft<s.length(); ft++) {bcache[ft][ft] = true;}
        for (int from =0; from<s.length()-1; from++) {
            bcache[from][from+1] = (s[from] == s[from+1]);
        }
        for (int sz=3; sz<=s.length(); sz++) {
            for (int from=0; from<s.length()-sz+1; from++) {
                bcache[from][from+sz-1] = (bcache[from+1][from+sz-1-1] && (s[from] == s[from+sz-1]));
            }
        }

        int cache[s.length()];
        cache[0] = 0; //this letter by itself is already a palindrome, requires no mincuts

        for (int ind=1; ind<s.length(); ind++) {
            if (isPalindrome_(0, ind)) {
                cache[ind] = 0;
                continue;
            }
            int mincut = std::numeric_limits<int>::max();
            for (int brk=ind-1; brk>=0; brk--) {
                if (!isPalindrome_(brk+1, ind)) continue;
                int cand = cache[brk] + 1;
                if (cand < mincut) mincut = cand;
            }
            cache[ind] = mincut;
        }
        return cache[s.length() - 1];
    }
};
