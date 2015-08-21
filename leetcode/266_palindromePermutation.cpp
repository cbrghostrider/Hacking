// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> chfreq;
        for (const char& ch : s) {
            auto it = chfreq.find(ch);
            if (it == chfreq.end()) {
                chfreq.insert(make_pair(ch, 1));
            } else {
                chfreq[ch]++;
            }
        }
        int numOdds = 0;
        for (const pair<char, int>& cip : chfreq) {
            if (cip.second % 2) numOdds++;
        } 
        return (numOdds <= 1);
    }
};
