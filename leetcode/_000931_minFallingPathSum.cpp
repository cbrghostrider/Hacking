class Solution {
public:
    // Recurrence:
    // fpsum(r, c) = mat[r, c] + min(fpsum(r+1, c-1), fpsum(r+1, c), fpsum(r+1, c+1))
    // O(n*m) runtime, O(n) space.
    int minFallingPathSum(vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        const int R=matrix.size();
        const int C=matrix[0].size();
        vector<int> fpsum(C, 0), temp(C, 0);
        
        // Base case, bottom row.        
        fpsum = matrix[R-1];
        
        // DP.
        for (int r=R-2; r>=0; r--) {
            for (int c=0; c<C; c++) {
                int cand_l = (c == 0 ? std::numeric_limits<int>::max() : fpsum[c-1]);
                int cand_m = fpsum[c];
                int cand_r = (c == C-1 ? std::numeric_limits<int>::max() : fpsum[c+1]);
                int cand_min = std::min(std::min(cand_l, cand_r), cand_m);
                temp[c] = matrix[r][c] + cand_min;
            }
            fpsum = temp;
        }
        
        // Final answer.
        int min = std::numeric_limits<int>::max();
        for (int c=0; c<C; c++) {
            if (fpsum[c] < min) {min = fpsum[c];}
        }
        return min;
    }
};
