class Solution {
public:
    // O(r*c) time, O(r + c) space.
    vector<int> luckyNumbers2 (vector<vector<int>>& matrix) {
        const int R = matrix.size();
        const int C = matrix[0].size();
        vector<int> row_mins(R, std::numeric_limits<int>::max());
        vector<int> col_maxs(C, std::numeric_limits<int>::min());
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (matrix[r][c] < row_mins[r]) {
                    row_mins[r] = matrix[r][c];
                }
                if (matrix[r][c] > col_maxs[c]) {
                    col_maxs[c] = matrix[r][c];
                }
            }
        }
        
        vector<int> ans;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (matrix[r][c] == row_mins[r] && matrix[r][c] == col_maxs[c]) {
                    ans.push_back(matrix[r][c]);
                }
            }
        }
        return ans;
    }
    
    // O(r*(c+r)) time, O(ans) space.
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        const int R = matrix.size();
        const int C = matrix[0].size();
        vector<int> ans;
        for (int r=0; r<R; r++) {
            int row_min = std::numeric_limits<int>::max();
            for (int c=0; c<C; c++) {
                if (matrix[r][c] < row_min) {
                    row_min = matrix[r][c];
                }
            }
            int col_ind = 0;
            for (; col_ind < C; col_ind++) {
                if (matrix[r][col_ind] == row_min) {
                    break;
                }
            }
            int col_max = std::numeric_limits<int>::min();
            for (int rp=0; rp<R; rp++) {
                if (matrix[rp][col_ind] > col_max) {
                    col_max = matrix[rp][col_ind];
                }
            }
            if (col_max == row_min) {
                ans.push_back(col_max);
            }
        }
        return ans;
    }
};
