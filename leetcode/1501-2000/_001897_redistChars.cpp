class Solution {
public:
    bool makeEqual(vector<string>& words) {
        int total = words.size();
        vector<int> freqs(26, 0);
        for (const string& word : words) {
            for (char ch : word) {freqs[ch-'a']++;}
        }
        for (int i=0; i<26; i++) {
            if (freqs[i] % total != 0) return false;
        }
        return true;
    }
};
