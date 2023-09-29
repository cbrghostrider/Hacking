// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    int sumOfSqr(int n) {
        int sum=0;
        while (n) {
            sum += ((n%10) * (n%10));
            n /= 10;
        }
        return sum;
    }
public:
    bool isHappy(int n) {
        if (n <= 0) return false;
        unordered_set<int> numset;
        numset.insert(n);
        while (1) {
            int sos = sumOfSqr(n);
            if (sos == 1) return true;
            if (numset.find(sos) != numset.end()) return false;
            numset.insert(sos);
            n = sos;
        }
    }
};
