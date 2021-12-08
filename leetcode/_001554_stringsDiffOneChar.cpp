class Solution {
    bool specialCompare(const string& s1, const string& s2) {
        int strike = 1;
        for (int i=0; i<s1.size(); i++) {
            if (s1[i] == s2[i]) continue;
            if (strike == 0) return false;
            strike--;
        }
        return (strike == 0);
    }
public:
    // O(n*n*m) time, O(1) space.
    bool differByOne_(vector<string>& dict) {
        const int N = dict.size();
        for (int i=0; i<N; i++) {
            for (int j=i+1; j<N; j++) {
                if (specialCompare(dict[i], dict[j])) return true;
            }
        }
        return false;
    }
    
    // O(m*m*n) time(?), O(m*n) space.
    // Hash table find/insert of word of length m should be O(m) time to insert that key.
    bool differByOne(vector<string>& dict) {
        unordered_set<string> altered;
        for (const string& word : dict) {
            string w = word;
            for (int i=0; i<word.size(); i++) {
                if (i != 0) {w[i-1] = word[i-1];}  // restoration of previous mutation
                w[i] = '.';  // mutate this position
                if (altered.find(w) != altered.end()) return true;
                altered.insert(w);
            }
        }
        return false;
    }
};
