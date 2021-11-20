class Solution {
    // Is substr of size 3 from [b, b+2] "good"?
    bool isGood(const string& s, int b) {
        return (s[b] != s[b+1] && s[b] != s[b+2] && s[b+1] != s[b+2]);
    }
public:
    int countGoodSubstrings(string s) {
        int count = 0;
        for (int i=0; i<(int)(s.size()-2); i++) {
            if (isGood(s, i)) {count++;}
        }
        return count;
    }
};
