class Solution {
public:
    // O(m*n) time, O(m*n) space.
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        const int m = grid.size();
        const int n = grid[0].size();
        vector<vector<int>> temp(m, vector<int>(n, 0));
        
        k = k % (m * n);  // After m*n shifts, we are back to original position.
        int row_moves = k / n;
        int col_shifts = k % n;
        for (int r=0; r<m; r++) {
            temp[(r + row_moves)%m] = grid[r];
        }
        for (int r=0; r<m; r++) {
            for (int c=0; c<n; c++) {
                int new_col = (c + col_shifts) % n;
                int new_row = (c + col_shifts >= n ? r+1 : r);
                new_row %= m;
                
                grid[new_row][new_col] = temp[r][c];
            }
        }
        return grid;
    }
};
