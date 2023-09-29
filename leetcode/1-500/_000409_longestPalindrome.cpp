class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> freqs;
        for (char ch : s) {freqs[ch]++;}
        int count=0;
        bool has_odd = false;
        for (const auto& kv : freqs) {
            if (kv.second % 2) {
                has_odd = true;
            }
            count += 2 * (kv.second/2);
        }
        return (has_odd ? count + 1 : count);
    }
};
