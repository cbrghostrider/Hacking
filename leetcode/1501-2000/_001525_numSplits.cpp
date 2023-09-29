class Solution {
public:
    int numSplits(string s) {
        if (s.size() <= 1) return 0;
        unordered_set<char> left, right;
        unordered_map<char, int> freqs;
        for (char ch : s) {freqs[ch]++; right.insert(ch);}
        
        int count=0;
        for (int i=1; i<s.size(); i++) {
            left.insert(s[i-1]);
            freqs[s[i-1]]--;
            if (freqs[s[i-1]] == 0) {right.erase(s[i-1]);}
            if (right.size() == left.size()) {count++;}
        }
        return count;
    }
};
