class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int R=grid.size(), C=grid[0].size();

        // DP initialization.
        vector<int> dp(grid.size(), 0), temp(grid.size(), 0);

        // Main DP loop.
        for (int c=C-2; c>=0; c--) {            
            for (int r=0; r<R; r++) {
                int cand1 = (r == 0   || grid[r-1][c+1] <= grid[r][c]) ? 0 : 1 + dp[r-1];
                int cand2 = (            grid[r]  [c+1] <= grid[r][c]) ? 0 : 1 + dp[r];
                int cand3 = (r == R-1 || grid[r+1][c+1] <= grid[r][c]) ? 0 : 1 + dp[r+1];
                int moves = std::max(cand1, std::max(cand2, cand3));
                temp[r] = moves;
            }
            dp = temp;
        }

        int ans=0;
        for (int r=0; r<R; r++) {
            ans = std::max(ans, dp[r]);
        }
        return ans;
    }
};
