class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        string ans(indices.size(), ' ');
        for (int i=0; i<indices.size(); i++) {
            ans[indices[i]] = s[i];
        }
        return ans;
    }
};
