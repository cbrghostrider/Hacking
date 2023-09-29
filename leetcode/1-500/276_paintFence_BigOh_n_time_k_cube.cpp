// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Really slow solution: O(n*k^3) time and O(k^2) space
// But easy to understand
// Currently gets TLE for n=3, k=1290
// Need to optimize further
//

class Solution {
public:
    int numWays(int n, int k) {
        if (n <= 0 || k <= 0) return 0;
        if (k == 1) return ((n <= 2) ? 1 : 0);
        if (n == 1) return k;
        if (n == 2) return (k*k);
        
        //ways to paint fence such that [rhs-1][rhs] posts are in their type of color
        vector<vector<int>> prev, next;
        prev = vector<vector<int>>(k, vector<int>(k, 1));
        next = vector<vector<int>>(k, vector<int>(k, 0));
        
        for (int step=2; step<n; step++) {
            for (int rhs=0; rhs<k; rhs++) {      //for next iteration this is the new post we are painting
                for (int p1=0; p1<k; p1++) {     //for next iteration, this is rhs-1 post
                    next[p1][rhs] = 0;
                    for (int p2=0; p2<k; p2++) { //for next iteration, this is rhs-2 post
                        next[p1][rhs] += (p1 == p2 && p2 == rhs) ? 0 : prev[p2][p1];
                    }
                }
            }
            prev = next;
        }
        
        int retval=0;
        for (int p1=0; p1<k; p1++) {
            for (int p2=0; p2<k; p2++) {
                retval += prev[p2][p1];
            }
        }
        return retval;
    }
};

