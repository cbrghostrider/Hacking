class Solution {
public:
    // Greedy algorithm.
    bool isSubsequence(string s, string t) {
        int s_ptr=0, t_ptr=0;
        while (s_ptr < s.size() && t_ptr < t.size()) {
            if (s[s_ptr] == t[t_ptr++]) s_ptr++; 
        }
        return (s_ptr == s.size());
    }
};
