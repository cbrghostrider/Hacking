class Solution {
public:
    // O(n) time, O(n) space.
    vector<int> partitionLabels(string s) {
        unordered_map<char, int> starts, ends;
        for (int i=0; i<s.size(); i++) {
            if (starts.find(s[i]) == starts.end()) {
                starts[s[i]] = i;
            }
        }
        for (int i=s.size()-1; i>=0; i--) {
            if (ends.find(s[i]) == ends.end()) {
                ends[s[i]] = i;
            }
        }
        vector<int> ans;
        int i_b=0, i=0;
        int opens = 0;  // all the open intervals currently
        while (i < s.size()) {
            if (starts[s[i]] == i) {
                if (opens == 0) {i_b = i;}
                opens++;
            }
            if (ends[s[i]] == i) {
                opens--;
                if (opens == 0) {
                    ans.push_back(i - i_b + 1);
                }
            }
            i++;
        }
        return ans;
    }
};
