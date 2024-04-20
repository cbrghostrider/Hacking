class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        const int R=grid.size(), C=grid[0].size();

        // Captures the "reach" of the bomb, if placed in this cell.
        // Overcounts by 1 if the cell itself contains an enemy.
        vector<vector<int>> reach(R, vector<int>(C, 0));

        // Accumulate column wise.        
        for (int c=0; c<C; c++) {            
            int count=0;
            for (int r=0; r<R+1; r++) {
                if (r == R || grid[r][c] == 'W') {
                    for (int ri = r-1; ri >= 0 && grid[ri][c] != 'W'; ri--) {
                        reach[ri][c] += count;
                    }
                    count=0;
                } else if (grid[r][c] == 'E') {
                    count++;
                }
            }
        }

        // Accumulate row wise.
        for (int r=0; r<R; r++) {            
            int count=0;
            for (int c=0; c<C+1; c++) {
                if (c == C || grid[r][c] == 'W') {
                    for (int ci = c-1; ci >= 0 && grid[r][ci] != 'W'; ci--) {
                        reach[r][ci] += count;
                    }
                    count=0;
                } else if (grid[r][c] == 'E') {
                    count++;
                }
            }
        }

        int best = 0;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 'W') continue;
                if (grid[r][c] == 'E') continue;
                int count = reach[r][c];
                best = std::max(best, count);                
            }
        }
        return best;
    }
};
