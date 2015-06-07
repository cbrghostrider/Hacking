// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// my initial version preserved all spaces... 
// leading, trailing, as well as multiple spaces between words
// but the testbench expected no extra spaces, so I had to change it

// compare to Haskell!
// reverseWordsInString = unwords . reverse . words

class Solution {
public:
    void reverseWords(string &s) {
        if (s.length() == 0) return;
        char space[] = " ";

        vector<string> words;
        while (s.length() != 0) {
            size_t start = s.find_first_not_of(space);
            if (start == string::npos) { s.erase(); break; }
            size_t end   = s.find_first_of(space, start);
            size_t len = (end == string::npos) ? (s.length() - start) : (end - start);
            string word = s.substr(start, len);
            words.push_back(word);
            s.erase(0, end);
        }
        
        s.clear();
        for (auto it = words.rbegin(); it != words.rend(); it++) {
            s += (*it); s += " ";
        }
        if (!(s.length() == 0)) s.erase(s.length() - 1);
    }
};
