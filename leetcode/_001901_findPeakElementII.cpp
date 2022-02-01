class Solution {
public:
    int R, C;
    
    // left and right are bounds of columns (inclusive).
    // Each recursive call, we split the #cols in half.
    // Hence O(n log m) time!
    vector<int> findPeak(const vector<vector<int>>& mat, int left, int right) {
        int mid = (left+right)/2;
        pair<int, int> max_cell = {0, mid};
        int max_val = mat[0][mid];
        
        int cleft  = mid-1 < 0 ? mid : mid-1;
        int cright = mid+1 == C ? mid : mid+1;
        for (int r=0; r<R; r++) {
            int my_max = std::max(std::max(mat[r][cleft], mat[r][cright]), mat[r][mid]);
            if (my_max > max_val) {
                max_val = my_max;
                if (my_max == mat[r][cleft])  {max_cell = {r, cleft};}
                if (my_max == mat[r][cright]) {max_cell = {r, cright};}
                if (my_max == mat[r][mid])    {max_cell = {r, mid};}
            }
        }
        
        if (right-left <= 2 || max_cell.second == mid) {
            return {max_cell.first, max_cell.second};
        }
        if (max_cell.second < mid) {
            return findPeak(mat, left, cleft);
        }
        return findPeak(mat, cright, right);
    }
    
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        R=mat.size();
        C=mat[0].size();
        return findPeak(mat, 0, C-1);
    }
    
    
    // Consider an algorithm where we:
    //   1. Find max value in a row
    //   2. Find max value in the col corresponding to #2
    //   3. Find max value in a row corresponding to #3
    //   ... and so on... alternating rows and cols.
    //   Each time we find a max, we test it for being the answer.
    //   Each alternation gives us +1 over the last value at least (new max).
    //
    // Problem limits are 500x500 = 250000 potential values
    // However note that only up to 100000 unique values are possible
    // 
    // Now putting the algorithm and these constraints together, 
    // We need no more than 100000 / 500 = 200 iterations of n and m together.
    //
    // STILL NOT O(m log n) tho...
    vector<int> findPeakGrid_(vector<vector<int>>& mat) {
        R=mat.size();
        C=mat[0].size();
        pair<int, int> last = {0, 0};
        bool check_row = true;
        
        while (1) {
            int limit = check_row ? R : C;            
            int max_val = mat[last.first][last.second];
            
            for (int k=0; k<limit; k++) {
                int r=check_row ? k : last.first;
                int c=!check_row ? k : last.second;
                if (max_val < mat[r][c]) {
                    last = {r, c};
                    max_val = mat[r][c];
                }
            }            
            if (isAnswer(mat, last)) {
                return {last.first, last.second};
            }            
            check_row = !check_row;
        }
        return {};  // should not get here
    }
    
    bool isAnswer(vector<vector<int>>& mat, pair<int, int> cell) {
        int r=cell.first, c=cell.second;
        bool upOK    = r == 0   || mat[r][c] > mat[r-1][c];
        bool downOK  = r == R-1 || mat[r][c] > mat[r+1][c];
        bool leftOK  = c == 0   || mat[r][c] > mat[r][c-1];
        bool rightOK = c == C-1 || mat[r][c] > mat[r][c+1];
        return (upOK && downOK && leftOK && rightOK);
    }
};
