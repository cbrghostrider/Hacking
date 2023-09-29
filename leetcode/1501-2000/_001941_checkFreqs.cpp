class Solution {
public:
    bool areOccurrencesEqual(string s) {
        if (s.size() <= 1) return true;
        unordered_map<char, int> freqs;
        for (char ch : s) {freqs[ch]++;}
        int freq=-1;
        for (const auto& kv : freqs) {
            if (freq == -1) {freq = kv.second;}
            else if (kv.second != freq) return false;
        }
        return true;
    }
};
