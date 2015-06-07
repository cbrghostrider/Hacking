// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        if (n <= 0) return vector<vector<int>>();
        vector<vector<int>> retval(n, vector<int>(n, 0));
        vector<int> nums;
        for (int i=1; i<=n*n; i++) nums.push_back(i);
        
        int layer=0, numInd=0;
        while (numInd < nums.size()) {
            int boundaryLo = layer;
            int boundaryHi = n-1-layer;
            //for odd numbers, only 1 number is left behind
            if ((n%2) && (numInd == nums.size()-1)) 
                retval[layer][layer] = nums[numInd++];
            for (int c=boundaryLo; c<boundaryHi && numInd < nums.size(); c++) 
                retval[boundaryLo][c] = nums[numInd++];
            for (int r=boundaryLo; r<boundaryHi && numInd < nums.size(); r++) 
                retval[r][boundaryHi] = nums[numInd++];
            for (int c=boundaryHi; c>boundaryLo && numInd < nums.size(); c--) 
                retval[boundaryHi][c] = nums[numInd++];
            for (int r=boundaryHi; r>boundaryLo && numInd < nums.size(); r--) 
                retval[r][boundaryLo] = nums[numInd++];
            layer++;
        }
        return retval;
    }
};
