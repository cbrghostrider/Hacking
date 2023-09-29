class Solution {
public:
    // O(n) time, O(1) space.
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> letters;
        for (char ch : magazine) {letters[ch]++;}
        for (char ch : ransomNote) {
            if (letters[ch] <= 0) return false;
            letters[ch]--;
        }
        return true;
    }
};
