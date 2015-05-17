//O(mn) time and O(mn) space
//The space could be optimized down to O(min(m, n)) by 
//keeping either only the left column or top row
//since the DP solution only needs last column or last row 
//depending upon way it is traversed (row wise or col wise)
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0) return 0; //invalid problem
        const int nrow = grid.size(), ncol = grid[0].size();
        
        //dynamic programming cache (min path from (0, 0) to (r, c))
        int cache[nrow][ncol];
        cache[0][0] = grid[0][0];
        
        //dynamic programming loop
        for (int r=0; r<nrow; r++) {
            for (int c=0; c<ncol; c++) {
                if (c == 0 && r == 0) continue;
                int candtop  = std::numeric_limits<int>::max();
                int candleft = std::numeric_limits<int>::max();
                if (r != 0) { //top exists
                    candtop  = cache[r-1][c] + grid[r][c];
                }
                if (c != 0) { //left exists
                    candleft = cache[r][c-1] + grid[r][c];
                }
                cache[r][c] = (candtop < candleft ? candtop : candleft);
            }
        }
        return cache[nrow-1][ncol-1];
    }
};
