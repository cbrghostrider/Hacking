class Solution {
public:
    // O(n^2) time, O(n) space.
    int maxRepeating(string sequence, string word) {
        if (word.size() > sequence.size()) return 0;
        
        vector<bool> repeats_at(sequence.size(), false);
        for (int i=0; i<=sequence.size()-word.size(); i++) {
            if (sequence.substr(i, word.size()) == word) {
                repeats_at[i] = true;
            }
        }
        
        int max=0;
        for (int i=0; i<sequence.size(); i++) {
            int len=0;
            for (int j=i; j<repeats_at.size(); j+=word.size()) {
                if (repeats_at[j]) {
                    len++;
                } else {
                    break;
                }
            }
            if (len > max) {max = len;}
        }
        return max;
    }
};
