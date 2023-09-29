// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int titleToNumber(string s) {
        return std::accumulate(s.begin(), s.end(), 0, [](const int& acc, const char& ch) -> int {
            return (acc*26 + (toupper(ch)-'A'+1));
        });
    }
};
