class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        const int m = mat.size();
        const int n = mat[0].size();
        if (m * n != r * c) {
            return mat;
        }
        vector<vector<int>> ans(r, vector<int>(c, 0));
        int ri=0, ci=0;
        for (int mi=0; mi<m; mi++) {
            for (int ni=0; ni<n; ni++) {
                if (ci==c) {
                    ri++;
                    ci = 0;
                }
                ans[ri][ci] = mat[mi][ni];
                ci++;
            }
        }
        return ans;
    }
};
