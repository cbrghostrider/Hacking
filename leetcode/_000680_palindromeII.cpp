class Solution {
    bool validPalindromeBetween(const string& s, int start, int end) {
        if (start > end) return false;
        if (start == end) return true;
        for (int i=start, j=end; i<j; i++, j--) {
            if (s[i] != s[j]) return false;
        }
        return true;
    }
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.size()-1;
        while (left < s.size() && right >= 0 && left < right && s[left] == s[right]) { left++; right--; }
        if (left >= right) return true;
        return (validPalindromeBetween(s, left, right-1) || validPalindromeBetween(s, left+1, right));
    }
};
