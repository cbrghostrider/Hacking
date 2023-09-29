class Solution {
    // Recurrence:
    // lp[r][c] = min(lp[r'][c'])
    //   where
    //     r' <- {r-1, r+1}; r' is within bounds
    //     c' <- {c-1, c+1}; c' is within bounds
    //     lp[r'][c'] > lp[r][c]
    
    // memoization cache 
    // [r][c] -> longest increasing path length
    vector<vector<int>> cache;
    int R, C;
    
    int lipLength(const vector<vector<int>>& matrix, int r, int c) {
        if (cache[r][c] != -1) {return cache[r][c];}
        
        int best=1;
        vector<pair<int, int>> neighs = {
            {r-1, c}, {r+1, c}, {r, c-1}, {r, c+1}
        };
        for (const auto& neigh : neighs) {
            int rp = neigh.first;            
            int cp = neigh.second;
            if (rp < 0 || rp >= R || cp < 0 || cp >= C) continue;
            if (matrix[rp][cp] <= matrix[r][c]) continue;
            int my_best = 1 + lipLength(matrix, rp, cp);
            best = std::max(my_best, best);
        }
        
        cache[r][c] = best;
        return best;
    }
    
public:
    // O(R*C) time, O(R*C) space.
    // We basically traverse each increasing path completely only once (so R*C cells traversed)
    // and perform no more than 4 checks per cell (R*C cells total)
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        R=matrix.size();
        C=matrix[0].size();
        
        cache = vector<vector<int>>(R, vector<int>(C, -1));
        
        int best=1;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                int my_path = lipLength(matrix, r, c);
                best = std::max(best, my_path);
            }
        }
        return best;
    }
};
