class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        if (original.size() != m*n) return {};
        vector<vector<int>> ans(m, vector<int>(n, 0));
        int i = 0;
        for (int r=0; r<m; r++) {
            for (int c=0; c<n; c++) {
                ans[r][c] = original[i++];
            }
        }
        return ans;
    }
};
