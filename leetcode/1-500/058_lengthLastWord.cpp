// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int lengthOfLastWord(string s) {
        //remove trailing whitespaces
        size_t size = s.find_last_not_of(" ");
        if (size == string::npos) return 0;
        s.erase(size+1);
        
        //find last word
        size = s.find_last_of(" ");
        return (size == string::npos ? s.length() : (s.length() - size - 1));
    }
};
