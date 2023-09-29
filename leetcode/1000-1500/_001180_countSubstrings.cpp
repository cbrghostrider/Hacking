class Solution {
public:
    int countLetters(string s) {
        int s_ptr = 0, count=0;
        while (s_ptr < s.size()) {
            int i_ptr = s_ptr;
            while (i_ptr < s.size() && s[s_ptr] == s[i_ptr]) { i_ptr++; }
            int n = i_ptr - s_ptr;
            count += (n * (n+1) / 2);
            s_ptr = i_ptr;
        }
        return count;
    }
};
