class Solution {
public:
    // solves the problem for partial concat as well.
    // not what the problem asks, but interesting nonetheless (and prob was unclear on it)
    bool isPrefixString2(string s, vector<string>& words) {
        int s_ptr = 0, w_ptr = 0;
        while (s_ptr < s.size() && w_ptr < words.size()) {
            if (s.size() - s_ptr >= words[w_ptr].size()) {
                for (int i=0; i<words[w_ptr].size(); i++) {
                    if (s[s_ptr + i] != words[w_ptr][i]) return false;
                }
                s_ptr += words[w_ptr].size();
                if (s.size() == s_ptr) return true;
                w_ptr++;
            } else {
                int count = s.size() - s_ptr;
                for (int i=0; i<count; i++) {
                    if (s[s_ptr + i] != words[w_ptr][i]) return false;
                }
                return true;
            }
        }
        return false;
    }
    
    // The problem when you can't match partial words.
     bool isPrefixString(string s, vector<string>& words) {
        int s_ptr = 0, w_ptr = 0;
        while (s_ptr < s.size() && w_ptr < words.size()) {
            if (s.size() - s_ptr >= words[w_ptr].size()) {
                for (int i=0; i<words[w_ptr].size(); i++) {
                    if (s[s_ptr + i] != words[w_ptr][i]) return false;
                }
                s_ptr += words[w_ptr].size();
                if (s.size() == s_ptr) return true;
                w_ptr++;
            } else {
                return false;
            }
        }
        return false;
     }
};
