class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        vector<int> freqs(26, 0);
        for (char c : chars) {freqs[c - 'a']++;} 
        
        int sum_len = 0;
        for (const string& word : words) {
            vector<int> ftable = freqs;
            bool possible = true;
            for (char c : word) {
                ftable[c - 'a']--;
                if (ftable[c - 'a'] < 0) {
                    possible = false;
                    break;
                }
            }
            if (possible) {sum_len += word.size();}
        }
        return sum_len;
    }
};
