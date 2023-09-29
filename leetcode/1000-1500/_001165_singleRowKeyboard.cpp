class Solution {
public:
    // O(n) time, O(1) space [since map is only 26 sized].
    int calculateTime(string keyboard, string word) {
        unordered_map<char, int> ch_to_ind;
        for (int i=0; i<26; i++) {
            ch_to_ind[keyboard[i]] = i;
        }
        int last = 0;
        int time = 0;
        for (char ch : word) {
            int next = ch_to_ind[ch];
            time += std::abs(next - last);
            last = next;
        }
        return time;
    }
};
