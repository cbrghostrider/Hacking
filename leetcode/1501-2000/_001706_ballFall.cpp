class Solution {
public:
    // Recurrence:
    // result(r, c) = 
    //    result (r+1, c+1) : if box[r][c] == 1 && box[r][c+1] == 1 (-1 if on the right edge)
    //    result (r+1, c-1) : if box[r][c] == -1 && box[r][c-1] == -1 (-1 if on the left edge)
    //    -1 ; Otherwise
    // O(m*n) time, O(n) space.
    vector<int> findBall(vector<vector<int>>& grid) {
        if (grid.empty()) return {};
        const int R=grid.size();
        const int C=grid[0].size();
        vector<int> result(C, -1), temp(C, -1);
        
        auto elem = [&grid, R, C](int ri, int ci) -> int {
            if (ci < 0) {return (grid[ri][0] == 1 ? -1 : 1);}
            if (ci >= C) {return (grid[ri][C-1] == 1 ? -1 : 1);}
            return grid[ri][ci];
        };
        
        // Base case.
        for (int c=0; c<C; c++) {
            result[c] = (elem(R-1, c) == elem(R-1, c + elem(R-1, c)) ? c + elem(R-1, c): -1);
        }
        
        // DP.
        for (int r=R-2; r>=0; r--) {
            for (int c=0; c<C; c++) {
                temp[c] = (elem(r, c) == elem(r, c + elem(r, c)) ? result[c + elem(r, c)] : -1);
            }
            result = temp;
        }
        
        return result;
    }
};
