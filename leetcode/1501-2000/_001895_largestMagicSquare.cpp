class Solution {
    // The number of rows and cols.
    int R=0, C=0;

    // The prefix sums, from L->R (for rows) and T->B (for cols).
    vector<vector<int>> pfs_rows;
    vector<vector<int>> pfs_cols;

    void computePrefixSums(const vector<vector<int>>& grid) {
        pfs_rows = vector<vector<int>>(R, vector<int>(C, 0));
        for (int r=0; r<R; r++) {
            int sum=0;
            for (int c=0; c<C; c++) {
                sum += grid[r][c];
                pfs_rows[r][c] = sum;
            }
        }
        pfs_cols = vector<vector<int>>(R, vector<int>(C, 0));
        for (int c=0; c<C; c++) {
            int sum=0;
            for (int r=0; r<R; r++) {
                sum += grid[r][c];
                pfs_cols[r][c] = sum;
            }
        }
    }

    int sum_tlbr_diag(const vector<vector<int>>& grid, int r, int c, int sz) {
        int sum=0;
        for (int ri=r, ci=c, si=0; si<sz; si++, ri++, ci++) {
            sum += grid[ri][ci];
        }
        return sum;
    }

    int sum_bltr_diag(const vector<vector<int>>& grid, int r, int c, int sz) {
        int sum=0;
        for (int ri=r+sz-1, ci=c, si=0; si<sz; si++, ri--, ci++) {
            sum += grid[ri][ci];
        }
        return sum;
    }

    bool isMagic(const vector<vector<int>>& grid, int r, int c, int sz) {
        if (sz == 1) return true;
        const int check_val = pfs_rows[r][c+sz-1] - (c == 0 ? 0 : pfs_rows[r][c-1]);

        // Checks rows.
        for (int ri=r; ri<r+sz; ri++) {
            int my_val = pfs_rows[ri][c+sz-1] - (c == 0 ? 0 : pfs_rows[ri][c-1]);
            if (my_val != check_val) return false;
        }
        // Check cols.
        for (int ci=c; ci<c+sz; ci++) {
            int my_val = pfs_cols[r+sz-1][ci] - (r == 0 ? 0 : pfs_cols[r-1][ci]);
            if (my_val != check_val) return false;
        }

        // Check top-left, bottom-right diag.
        int sum_tlbr = sum_tlbr_diag(grid, r, c, sz);
        if (sum_tlbr != check_val) return false;

        // check bottom-left, top-right diag.
        int sum_bltr = sum_bltr_diag(grid, r, c, sz);
        if (sum_bltr != check_val) return false;

        return true;
    }
public:
    // O(n^4) runtime; O(n^2) space.
    int largestMagicSquare(vector<vector<int>>& grid) {
        R = grid.size();
        C = grid[0].size();
        computePrefixSums(grid);

        const int MINVAL = std::min(R, C);
        for (int sz=MINVAL; sz >= 1; sz--) {  // Check increasingly smaller sizes of squares.
            for (int r=0; r<=R-sz; r++) {
                for (int c=0; c<=C-sz; c++) {
                    if (isMagic(grid, r, c, sz)) {
                        return sz;
                    }
                }
            }
        }

        return 1;
    }
};
