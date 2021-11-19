class Solution {
public:
    // O(n) time, O(n) space.
    int maxLengthBetweenEqualCharacters(string s) {
        std::unordered_map<char, int> opened_at;
        int max = -1;
        for (int i=0; i<s.size(); i++) {
            char ch = s[i];
            if (opened_at.find(ch) != opened_at.end()) {
                int len = i-opened_at[ch]-1;
                if (len > max) {
                    max = len;
                }
            } else {
                opened_at[ch] = i;
            }
        }
        return max;
    }
};
