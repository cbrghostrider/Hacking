// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// A bit ugly, need to refactor
//
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);
    int number;
class Solution {
    long firstBadVersion(long n, long stepsize) {
        if (stepsize == 1 && isBadVersion(n)) return (n);
        if (!isBadVersion(n)) {
            long jumpto = n+stepsize;
            if (jumpto > number && stepsize == 1) {
                return number; //error case
            } else if (jumpto > number) {
                return firstBadVersion(n+1, 1);
            } else {
                return firstBadVersion(jumpto, stepsize*2);
            }
        }
        return firstBadVersion(n-(stepsize/2)+1, 1);
    }
public:
    int firstBadVersion(int n) {
        //if (isBadVersion(1)) return 1;
        number = n;
        return firstBadVersion(1, 1);
    }
};

