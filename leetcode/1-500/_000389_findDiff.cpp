class Solution {
public:
    // O(n) time, O(1) space (only 26 chars).
    char findTheDifference(string s, string t) {
        unordered_map<char, int> s_freq;
        unordered_map<char, int> t_freq;
        for (char ch : s) {s_freq[ch]++;}
        for (char ch : t) {t_freq[ch]++;}
        for (char ch : t) {
            if (s_freq[ch] != t_freq[ch]) return ch;
        }
        return ' ';
    }
};
