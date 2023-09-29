class Solution {
    int R=0, C=0;
    
    // return true if the island is closed.
    // performs a dfs to properly account for the whole island
    bool accumulate(vector<vector<int>>& grid, int row, int col) {
        vector<pair<int, int>> stack;
        stack.push_back({row, col}); 
        grid[row][col] = '.';  // mark visited
        bool ret = true;
        
        while (!stack.empty()) {
            pair<int, int> rc = stack.back();
            stack.pop_back();
            int r=rc.first, c=rc.second;
            
            if (r == 0 || r == R-1 || c == 0 || c == C-1) {
                ret = false;
            }
            if (r != 0 && grid[r-1][c] == 0) {    // N exists and is land.
                grid[r-1][c] = '.';
                stack.push_back({r-1, c});
            }
            if (r != R-1 && grid[r+1][c] == 0) {  // S exists and is land.
                grid[r+1][c] = '.';
                stack.push_back({r+1, c});
            }
            if (c != 0 && grid[r][c-1] == 0) {    // W exists and is land.
                grid[r][c-1] = '.';
                stack.push_back({r, c-1});                
            }
            if (c != C-1 && grid[r][c+1] == 0) {  // E exists and is land.
                grid[r][c+1] = '.';
                stack.push_back({r, c+1});                
            }
        }
        return ret;
    }
public:
    int closedIsland(vector<vector<int>>& grid) {
        R=grid.size();
        C=grid[0].size();
        int count=0;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 0) {
                    bool is_closed = accumulate(grid, r, c);
                    if (is_closed) count++;
                }
            }
        }
        return count;
    }
};
