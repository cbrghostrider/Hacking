// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int nrows = matrix.size();    if (nrows == 0) return false;
        int ncols = matrix[0].size(); if (ncols == 0) return false;
        
        int rctr = 0, cctr = ncols-1; 
        
        while (rctr < nrows && cctr >= 0) {
            if (target == matrix[rctr][cctr]) {
                return true;
            } else if (target < matrix[rctr][cctr]) { //cannot be below this diagonal
                cctr--;
            } else {
                rctr++;
            }
        }
        
        return false;
    }
};
