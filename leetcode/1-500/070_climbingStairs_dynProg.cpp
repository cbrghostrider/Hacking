// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// O(n) time and O(n) space
// Since we only need previous 2 ways, space can be reduced to O(1)
class Solution {
public:
    int climbStairs(int n) {
        
        //dynamic programming cache
        int ways[n+1];
        ways[0] = 0; ways[1] = 1; ways[2] = 2;
        
        //dynamic programming loop
        for (int s=3; s<=n; s++) {
            ways[s] = ways[s-1] + ways[s-2];
        }
        
        return ways[n];
    }
};
