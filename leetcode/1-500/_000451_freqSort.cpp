class Solution {
public:
    // O(n) space, O(n log n) time.
    string frequencySort(string s) {
        unordered_map<char, int> freqs;
        for (char ch : s) {freqs[ch]++;}
        std::sort(s.begin(), s.end(), [&freqs](char lhs, char rhs) -> bool {
            if  (freqs[lhs] != freqs[rhs]) {
                return freqs[lhs] > freqs[rhs];
            }
            return lhs > rhs;
        });
        return s;
    }
};
