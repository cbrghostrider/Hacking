class Solution {
public:
    // To solve it in place, we use a little trick.
    // The board only has 1's and 0's. But uses int (32 bits) to represent the number.
    // We can solve for a cell, and place its value in the top 16 bits.
    // While solving for any cell, we zero out the top 16 bits, so we know not to use future values.
    // When done, we right shift everything by 16.
    void gameOfLife(vector<vector<int>>& board) {
        uint32_t GET_LOWER = 0x0000ffff;
        uint32_t SHIFT = 16;
        const int R=board.size();
        const int C=board[0].size();
        
        // Does not do bounds checking.
        auto getPrevValue = [&board, GET_LOWER](int r, int c) -> int {
            return (board[r][c] & GET_LOWER);
        };
        
        // Does not do bounds checking.
        auto putNonDestructive = [&board, GET_LOWER, SHIFT](int r, int c, bool alive) {
            uint32_t val = alive ? 1 : 0;
            board[r][c] = ((board[r][c] & GET_LOWER) | (val << SHIFT));
        };
        
        auto evalCell = [&board, putNonDestructive, getPrevValue, R, C](int r, int c) {
            int neigh_alive=0;
            if (r != 0)               { neigh_alive += getPrevValue(r-1, c);}
            if (r != R-1)             { neigh_alive += getPrevValue(r+1, c); }
            if (c != 0)               { neigh_alive += getPrevValue(r, c-1); }
            if (c != C-1)             { neigh_alive += getPrevValue(r, c+1); }
            if (r != 0 && c != 0)     { neigh_alive += getPrevValue(r-1, c-1); }
            if (r != 0 && c != C-1)   { neigh_alive += getPrevValue(r-1, c+1); }
            if (r != R-1 && c != 0)   { neigh_alive += getPrevValue(r+1, c-1); }
            if (r != R-1 && c != C-1) { neigh_alive += getPrevValue(r+1, c+1); }
            
            int my_val = getPrevValue(r, c);
            if (my_val == 1 && neigh_alive < 2) {
                putNonDestructive(r, c, /*alive=*/false);
            } else if (my_val == 1 && (neigh_alive == 2 || neigh_alive == 3)) {
                putNonDestructive(r, c, /*alive=*/true);
            } else if (my_val == 1 && neigh_alive > 3 ) {
                putNonDestructive(r, c, /*alive=*/false);
            } else if (my_val == 0 && neigh_alive == 3) {
                putNonDestructive(r, c, /*alive=*/true);
            } else if (my_val == 0) {
                putNonDestructive(r, c, /*alive=*/false);
            }
        };
        
        auto finalizeCell = [&board, SHIFT](int r, int c) {
            board[r][c] >>= SHIFT;
        };
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                evalCell(r, c);
            }
        }
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                finalizeCell(r, c);
            }
        }
    }
};
