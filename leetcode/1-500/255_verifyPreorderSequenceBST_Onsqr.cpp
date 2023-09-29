// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Current TLE on large inputs, because the algorithm is O(n^2)
// Need to find a O(n) algorithm
//
class Solution {
public:
    bool verify(vector<int>& preorder, int from, int to) {
        if (from >= to) return true;
        int me = preorder[from];
        
        int boundary = from+1;
        while (boundary <= to && preorder[boundary] < me) {
            boundary++;
        }
        for (int i=boundary; i<=to; i++) {
            if (preorder[i] <= me) return false;
        }
        return (verify(preorder, from+1, boundary-1) && verify(preorder, boundary, to));
    }
    bool verifyPreorder(vector<int>& preorder) {
        if (preorder.size() == 0) return true;
        return verify(preorder, 0, preorder.size()-1);
    }
};
