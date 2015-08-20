// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// Although the loop is O(n^2) iterations, work done per iteration is O(n) due to check for palindrome
// Need to precompute and cache those results to make this truly O(n^2)
class Solution {
    bool isPalindrome_(const string& s) {
        for (int i=0; i<s.length()/2; i++) {
            if (s[i] != s[s.length()-1-i]) return false;
        }
        return true;
    }
public:
    int minCut(string s) {
        if (s.length() == 0) return 0;

        int cache[s.length()];
        cache[0] = 0; //this letter by itself is already a palindrome, requires no mincuts

        for (int ind=1; ind<s.length(); ind++) {
            if (isPalindrome_(s.substr(0, ind+1))) {
                cache[ind] = 0;
                continue;
            }
            int mincut = std::numeric_limits<int>::max();
            for (int brk=ind-1; brk>=0; brk--) {
                string ss = s.substr(brk+1, ind+1);
                if (!isPalindrome_(ss)) continue;
                int cand = cache[brk] + 1;
                if (cand < mincut) mincut = cand;
            }
            cache[ind] = mincut;
        }
        return cache[s.length() - 1];
    }
};
