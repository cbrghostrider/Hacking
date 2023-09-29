class Solution {
public:
    // O(n) time, O(1) space.
    int firstUniqChar(string s) {
        unordered_map<char, int> letters;
        for (char ch : s) {letters[ch]++;}
        for (int i=0; i<s.size(); i++) {
            if (letters[s[i]] == 1) return i;
        }
        return -1;
    }
};
