// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
        int sqlen = 0;
        
        //dynamic programming cache
        vector<vector<int>> cache(matrix.size(), vector<int>(matrix[0].size(), 0));
        
        //base cases
        for (int i=0; i<matrix.size(); i++)    { 
            cache[i][0] = (matrix[i][0] == '1') ? 1 : 0; 
            if (cache[i][0] == 1) sqlen = 1;
        }
        for (int i=0; i<matrix[0].size(); i++) { 
            cache[0][i] = (matrix[0][i] == '1') ? 1 : 0; 
            if (cache[0][i] == 1) sqlen = 1;
        }
        
        //dynamic programming algorithm
        for (int r=1; r<matrix.size(); r++) {
            for (int c=1; c<matrix[0].size(); c++) {
                if (matrix[r][c] == '0') { cache[r][c] = 0; continue; }
                cache[r][c] = min(cache[r-1][c-1], min(cache[r-1][c], cache[r][c-1])) + 1;
                if (cache[r][c] > sqlen) { sqlen = cache[r][c]; }
            }
        }
        return sqlen*sqlen;
    }
};
