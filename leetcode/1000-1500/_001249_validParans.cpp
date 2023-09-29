class Solution {
public:
    // O(n) time, O(n) space.
    string minRemoveToMakeValid(string s) {
        vector<int> opens;
        unordered_set<int> deletes;
        
        for (int i=0; i<s.size(); i++) {
            char ch = s[i];
            if (ch == '(') {
                opens.push_back(i);
            } else if (ch == ')') {
                if (opens.size() > 0) {
                    opens.pop_back();
                } else {
                    deletes.insert(i);
                }
            }
        }
        for (int i=0; i<opens.size(); i++) {
            deletes.insert(opens[i]);
        }
        string ret;
        for (int i=0; i<s.size(); i++) {
            if ((s[i] == '(' || s[i] == ')') && deletes.find(i) != deletes.end()){
                continue;
            }
            ret.push_back(s[i]);
        }       
        return ret;
    }
};
