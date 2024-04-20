class Solution {
    // Start with a grid of all zeros.
    // Flip each column, only if needed, so that the first element matches.
    // Now flip each row, only if needed, so that the first element matches.
    // If after this, the grid matches the input, there is a solution.
    // Else not.

    void flip_column(vector<vector<int>>& my_grid, int col, int R) {
        for (int i=0; i<R; i++) {
            my_grid[i][col] = 1 - my_grid[i][col];
        }
    }

    void flip_row(vector<vector<int>>& my_grid, int row, int C) {
        for (int i=0; i<C; i++) {
            my_grid[row][i] = 1 - my_grid[row][i];
        }
    }

    bool are_same(const vector<vector<int>>& g1, const vector<vector<int>>& g2, int R, int C) {
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (g1[r][c] != g2[r][c]) return false;
            }
        }
        return true;
    }
public:
    bool removeOnes(vector<vector<int>>& grid) {
        const int R=grid.size(), C=grid[0].size();

        vector<vector<int>> my_grid(R, vector<int>(C, 0));
        for (int i=0; i<C; i++) {
            if (my_grid[0][i] != grid[0][i]) {
                flip_column(my_grid, i, R);
            }
        }
        for (int i=0; i<R; i++) {
            if (my_grid[i][0] != grid[i][0]) {
                flip_row(my_grid, i, C);
            }
        }
        return are_same(grid, my_grid, R, C);
    }
};
