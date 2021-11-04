class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        const int M = matrix.size();
        const int N = matrix[0].size();
        vector<vector<int>> ans(N, vector<int>(M, 0));
        for (int mi=0; mi<M; mi++) {
            for (int ni=0; ni<N; ni++) {
                ans[ni][mi] = matrix[mi][ni];
            }
        }
        return ans;
    }
};
