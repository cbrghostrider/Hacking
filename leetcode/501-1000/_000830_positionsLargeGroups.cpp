class Solution {
public:
    vector<vector<int>> largeGroupPositions(string s) {
        vector<vector<int>> ans;
        int s_ptr = 0;
        while (s_ptr < s.size()) {
            int e_ptr = s_ptr;
            while (e_ptr < s.size() && s[s_ptr] == s[e_ptr]) { e_ptr++;}
            if (e_ptr - s_ptr >= 3) {ans.push_back({s_ptr, e_ptr-1});}
            s_ptr = e_ptr;
        }
        return ans;
    }
};
