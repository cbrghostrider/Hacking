class Solution {
public:
    // O(n^2) time, O(1) space.
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size()) return false;
        for (int d=0; d<s.size(); d++) {
            bool match = true;
            for (int i=0; i<s.size(); i++) {
                int pos = (i + d) % s.size();
                if (s[i] != goal[pos]) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }
        return false;
    }
};
