// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.size() == 0) return 0;
        int hp=0, np=0;
        for (hp=0; hp <= ((int)(haystack.size()) - (int)(needle.size())); hp++) {
            for (np=0; np < needle.size(); np++) {
                if (haystack[hp+np] != needle[np]) break;
            }
            if (np == needle.size()) return hp;
        }
        return -1;
    }
};
