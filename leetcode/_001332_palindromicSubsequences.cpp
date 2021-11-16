class Solution {
    bool isPalindromeBetween(const string& s, int start, int end) {
        while (start < end) {
            if (s[start++] != s[end--]) return false;
        }
        return true;
    }
public:
    int removePalindromeSub(string s) {
        return (isPalindromeBetween(s, 0, s.size()-1) ? 1 : 2);
    }
};
