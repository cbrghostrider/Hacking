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
