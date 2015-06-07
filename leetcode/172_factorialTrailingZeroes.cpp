// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//Consider any number n for which we want to find the # of trailing zeros in n! (n factorial)
//e.g. if you consider n=7, you will realize that the only way to get a trailing
//zero is to get one 2 and one 5 to multiply together (sure, you can have a 10 itself
//but it is just a combination of 2x5)
//consider the final digit of any of the individual numbers in the sequence: 1x2x3x.....xn
//This final digits can be anything from 0 to 9
//the 1, 3, 7 do not contribute anything, 
//the 2, 4, 6, 8 contribute 2s
//the 5s contribute 5s
//The 0s contribute both 2 and 5
//In other words, the availability of 2s grows far quicker than that of 5s
//So if you just count the number of multiples of 5, you should get # of trailing zeros.
//
//There is one caveat though. Consider n=30. 
//Now you have crossed 5x5=25. This multiple of 5 contributes not just one, but two 5s!!!
//Similarly, multiples of 125 contribute three 5s, and so on.
//Therefore the total number of zeros in n! is:
//(n/5) + (n/25) + (n/125) + ..... and so on
//
//conversion to long is needed to avoid mult overflowing in the solution below.
//The algorithmic complexity of this solution is O(log-base-5 of n)
class Solution {
public:
    int trailingZeroes(int n) {
        long nl = (long) n;
        long zeros=0;
        long mult = 5;
        while (n/mult) {
            zeros += (n/mult);
            mult *= 5;
        }
        return zeros;
    }
};
