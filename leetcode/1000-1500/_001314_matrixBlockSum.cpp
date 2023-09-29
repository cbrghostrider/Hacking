class Solution {
public:
    // O(R*C*K) time, O(R*C) space.
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        const int R = mat.size();
        const int C = mat[0].size();
        vector<vector<int>> ans(R, vector<int>(C, 0));
        vector<vector<int>> csum_row = ans;
        
        for (int r=0; r<R; r++) {
            int sum=0;
            for (int c=0; c<C; c++) {
                sum += mat[r][c];
                csum_row[r][c] = sum;
            }
        }   
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                int sum=0;
                
                int cl = c-k, cr = c+k;
                if (cl < 0) {cl=0;}
                if (cr >= C) {cr = C-1;}
                
                for (int d=-k; d<=k; d++) {
                    int ri=r+d;
                    if (ri < 0 || ri >= R) continue;
                    
                    sum += csum_row[ri][cr] - csum_row[ri][cl] + mat[ri][cl];
                }
                ans[r][c] = sum;
            }
        }
        return ans;
    }
};
