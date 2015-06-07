// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        int R[m+n] = {0};
        int ri = 0, ai=0, bi=0;
        while (ri < m+n) {
            if (ai >= m && bi >= n) {
                assert(0); //impossible
            } else if (ai >= m) {
                    R[ri++] = B[bi++];                
            } else if (bi >= n) {
                    R[ri++] = A[ai++];                
            } else {
                if (A[ai] < B[bi]) {
                    R[ri++] = A[ai++];
                } else {
                    R[ri++] = B[bi++];
                }
            }
        }
        
        if ((m+n) % 2) {
            return R[((m+n)/2)];
        } else {
            return ((double)(R[((m+n)/2) - 1] + R[((m+n)/2)])) / 2.0;
        }
    }
};

