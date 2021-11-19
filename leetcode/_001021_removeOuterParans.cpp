class Solution {
public:
    string removeOuterParentheses(string s) {
        string ans;
        int s_ptr = 0; 
        while (s_ptr < s.size()) {
            int e_ptr = s_ptr + 1;
            int opens = 1;
            while (e_ptr < s.size()) {
                if (s[e_ptr] == '(') {
                    opens++;
                } else {
                    opens--;
                }
                e_ptr++;
                if (opens == 0) {
                    ans += s.substr(s_ptr+1, e_ptr-s_ptr-2);
                    break;
                }
            }
            s_ptr = e_ptr;
        }
        return ans;
    }
};
