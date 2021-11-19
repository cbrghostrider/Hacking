class Solution {
public:
    bool buddyStrings(string s, string goal) {
        if (s.size() != goal.size()) return false;
        int num_unequal = 0;
        bool has_duplicate = false;
        unordered_set<char> charset;
        int index1 = -1, index2 = -1;  // index of first two mismatches.
        for (int i=0; i<s.size(); i++) {
            if (charset.find(s[i]) != charset.end()) {has_duplicate = true;}
            charset.insert(s[i]);
            
            if (s[i] != goal[i]) {
                num_unequal++;
                if (index1 == -1) {index1 = i;}
                else if (index2 == -1) {index2 = i;}
            }
        }
        if (num_unequal == 0) { return has_duplicate; }
        if (num_unequal == 1 || num_unequal >= 3) {return false;}
        if (num_unequal == 2) {
            return (s[index1] == goal[index2] && s[index2] == goal[index1]);
        }
        return false;  // should not get here
    }
};
