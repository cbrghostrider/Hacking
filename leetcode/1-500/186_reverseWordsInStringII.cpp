// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    void reverseWords(string &s) {
        if (s.size() == 0) return;
        string spaces(" \t\n");
        int start = s.find_first_of(spaces, 0);
        if (start == string::npos) return;

        std::reverse(s.begin(), s.end());
        int end = 0;
        start = s.find_first_not_of(spaces, 0);
        
        while ((end = s.find_first_of(spaces, start)) != string::npos) {
            std::reverse(s.begin()+start, s.begin()+end);
            start = s.find_first_not_of(spaces, end);
            if (start == string::npos) return;
        }
        std::reverse(s.begin()+start, s.end());
        return;
    }
};

