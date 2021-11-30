class Solution {
public:
    // let lrs(i) be the longest repeating substring length up to index i.
    // lrs(i) = max(lrs(i-1), max len of choices)
    //   where choices = all substrings that end at current index, and repeated so far
    // O(n^3) time, O(n) space.
    // Time is O(n^3) due to string construct/compare.
    int longestRepeatingSubstring(string s) {
        if (s.size() == 0) return 0;
        unordered_set<string> found;
        vector<int> lrs(s.size(), 0);
        
        // Base case.
        lrs[0] = 0;
        found.insert(s.substr(0, 1));
        
        // DP.
        for (int i=1; i<s.size(); i++) {
            int max = lrs[i-1];
            for (int len=1; len<=i+1; len++) {
                string ss = s.substr(i-len+1, len);
                bool is_present = (found.find(ss) != found.end());
                found.insert(ss);
                if (!is_present) {continue;}
                if (len > max) {max = len;}
            }
            lrs[i] = max;
        }
        
        return lrs[s.size()-1];
    }
};
