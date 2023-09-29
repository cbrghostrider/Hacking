class Solution {
public:
    // O(n^2 + kn) time, O(n^2) space; n=grid size, k=num of mines.
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        // Initialization.
        vector<vector<int>> grid(n, vector<int>(n, 1));
        for (int r=0; r<n; r++) {
            for (int c=0; c<n; c++) {
                grid[r][c] = std::min(std::min(r+1, c+1), 
                                      std::min(n-r, n-c));
            }
        }
        
        // Corruption.
        for (const auto& mine : mines) {
            int r=mine[0], c=mine[1];
            grid[r][c] = 0;
            for (int ri=r-1, d=1; ri>=0; ri--, d++) {
                if (grid[ri][c] == 0) break;
                if (grid[ri][c] > d) {
                    grid[ri][c] = d;
                }
            }
            for (int ri=r+1, d=1; ri<n; ri++, d++) {
                if (grid[ri][c] == 0) break;
                if (grid[ri][c] > d) {
                    grid[ri][c] = d;
                }
            }
            for (int ci=c-1, d=1; ci>=0; ci--, d++) {
                if (grid[r][ci] == 0) break;
                if (grid[r][ci] > d) {
                    grid[r][ci] = d;
                }
            }
            for (int ci=c+1, d=1; ci<n; ci++, d++) {
                if (grid[r][ci] == 0) break;
                if (grid[r][ci] > d) {
                    grid[r][ci] = d;
                }
            }
        }
        
        // Inspection.
        int best=0;
        for (int r=0; r<n; r++) {
            for (int c=0; c<n; c++) {
                best = std::max(best, grid[r][c]);
            }
        }
        return best;
    }
};
