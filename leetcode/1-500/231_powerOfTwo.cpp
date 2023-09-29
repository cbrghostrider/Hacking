// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Two ways to check power of two.
// Both are O(1)
//
class Solution {
public:
    /*bool isPowerOfTwo(int n) {
        return (n > 0 && ((n & (n-1)) == 0));
    }
    */
    bool isPowerOfTwo(int n) {
        return (n > 0 && n == (n & (-n)));
    }
};
