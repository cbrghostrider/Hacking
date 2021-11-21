class Solution {
public:
    bool isDecomposable(string s) {
        int s_ptr=0;
        int strikes = 1;
        while (s_ptr < s.size()) {
            int e_ptr=s_ptr;
            while (e_ptr < s.size() && s[s_ptr] == s[e_ptr]) {e_ptr++;}
            int ss_len = e_ptr-s_ptr;
            if (ss_len % 3 == 2) {
                if (strikes > 0) {strikes--;} else {return false;}
            } else if (ss_len % 3 != 0) {return false;}
            s_ptr = e_ptr;
        }
        return (strikes==0);
    }
};
