class Solution {
public:
    bool checkAlmostEquivalent(string word1, string word2) {
        vector<int> freqs1(26, 0), freqs2(26, 0);
        for (char ch : word1) {freqs1[ch-'a']++;}
        for (char ch : word2) {freqs2[ch-'a']++;}
        for (int i=0; i<26; i++) {
            if (std::abs(freqs1[i] - freqs2[i]) > 3) return false;
        }
        return true;
    }
};
