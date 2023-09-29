// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Weird. Getting correct answer for one specific test case on my local machine, but
// leetcode Online Judge says my answer on its machine is different. 
// I faced same problem in another question today, my machine shows expected answer.
// Not sure what is up with OJ.
//

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        //differ by 1 or more in size
        if (abs(s.length() - t.length()) >= 2) return false;
        
        //same length strings
        if (s.length() == t.length()) {
            for (int ptr=0; ptr<s.length(); ptr++) {
                if (s[ptr] != t[ptr]) {
                    return (s.substr(ptr+1) == t.substr(ptr+1));
                }
            }
            return false;
        }
        
        //differ by exactly 1 in length
        bool sIsBigger = s.length() > t.length();
        int smallLen = (sIsBigger ? t.length() : s.length());
        for (int ptr=0; ptr<smallLen; ptr++) {
            if (s[ptr] != t[ptr]) {
                if (sIsBigger) {
                    return (s.substr(ptr+1) == t.substr(ptr));
                } else {
                    return (s.substr(ptr) == t.substr(ptr+1));
                }
            }
        }
        return true;
    }
};
