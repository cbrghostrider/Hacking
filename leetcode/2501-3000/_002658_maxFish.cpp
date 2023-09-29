// O(m*n) solution.
// Each cell is visited at most 5 times.
// Once in the main double loop, and once from each of its 4 neighbors.
class Solution {
    int R=0, C=0;
    void compute(vector<vector<int>>& grid, int r, int c, int& local) {
        if (r < 0 || r >= R || c < 0 || c >= C) return;
        if (grid[r][c] == 0) return;
        local += grid[r][c];
        grid[r][c] = 0;
        compute(grid, r-1, c, local);
        compute(grid, r+1, c, local);
        compute(grid, r, c-1, local);
        compute(grid, r, c+1, local);
    }
public:
    int findMaxFish(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        R=grid.size(), C=grid[0].size();

        int max=0;
        for (int ri=0; ri<R; ri++) {
            for (int ci=0; ci<C; ci++) {
                int local = 0;
                compute(grid, ri, ci, local);
                if (local > max) {max = local;}
            }
        }
        return max;
    }
};
