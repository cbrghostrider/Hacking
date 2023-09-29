class Solution {
    // Eat backspaces.
    string process(const string& s) {
        string ret;
        for (char c : s) {
            if (c == '#') {
                if (!ret.empty()) ret.pop_back();
            } else {
                ret.push_back(c);
            }
        }
        return ret;
    }
    
    void eatBackspace(const string& s, int& s_ptr) {
        int s_bp=0;
        while (s_ptr >= 0 && (s_bp || s[s_ptr] == '#')) {
            if (s[s_ptr--] == '#') s_bp++; else s_bp--;
        }
    }
public:
    // O(n) space, O(n) time.
    bool backspaceCompare2(string s, string t) {
        string sp = process(s);
        string tp = process(t);
        if (sp.size() != tp.size()) return false;
        for (int i=0; i<sp.size(); i++) {
            if (sp[i] != tp[i]) return false;
        }
        return true;
    }
    
    // O(1) space, O(n) time.
    bool backspaceCompare(string s, string t) {
        int s_ptr = s.size()-1, t_ptr = t.size()-1;
        while (s_ptr >= 0 && t_ptr >= 0) {
            if (s[s_ptr] != '#' && t[t_ptr] != '#') {
                if (s[s_ptr--] != t[t_ptr--]) return false;
                continue;
            } 
            
            // Get next non-backspace char, accounting for backspaces encountered and eliminating chars.
            eatBackspace(s, s_ptr);
            eatBackspace(t, t_ptr);
        }
        
        // Leading letter-backspace combos may cancel out to be nothing.
        eatBackspace(s, s_ptr);
        eatBackspace(t, t_ptr);
        
        return (s_ptr == -1 && t_ptr == -1);
    }
};

