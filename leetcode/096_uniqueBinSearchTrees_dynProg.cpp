// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int numTrees(int n) {
        if (n <= 1) return 1;
        //index i stores: How many binary trees with i nodes?
        int cache[n+1];
        
        //base cases
        cache[0] = cache[1] = 1;
        
        //dynamic programming loop
        for (int nodes=2; nodes <= n; nodes++) {
            int numtrees = 0;
            for (int root=1; root <= nodes; root++) {
                int lhs = cache[root-1];
                int rhs = cache[nodes-root];
                numtrees += lhs*rhs;
            }
            cache[nodes] = numtrees;
        }
        return cache[n];
    }
};
