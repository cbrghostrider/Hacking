// Leetcode.com, problem #29.
// Problem is to divide two integers, WITHOUT using multiplication, division, or modulus operators.
//
// First consider the naive solution. Repeated subtraction. Subtract the divisor repeatedly from 
// the dividend, keeping track of how many times you do this. Process ends when dividend < divisor, and
// the number of times we subtracted is the quotient. 
// The naive solution is functionally correct, but the problem is its runtime. In particular, runtime 
// is O(n) where n is the dividend value. 
// for example, consider MAX_INT / 1. This process will take forever, because we are subtracting 1 at 
// every step from MAX_INT.
//
// In order to speed up this process, we have to use the principles of binary search. The key is that 
// instead of subtracting divisor at every step, we will DOUBLE the divisor at every step and 
// subtract that. Obviously the quotient now increases in steps of 1, 2, 4, 8...  etc, and hence
// his process becomes logarithmic in nature i.e. runtime is O(log n).
//
// A caveat is that when we reach dividend < divisor, we are NOT necessarily done. This is because the 
// divisor is no longer our original divisor, but it is divisor * (some multiple of 2).
// Now we need to recurse on the new dividend, but with the original divisor (and stepsize of 1 again)!
// Adding this recursive quotient, to our computed quotient, we can get the final answer.

class Solution {
    long dividePrime(long dividend, long deno) {
        long divisor  = deno;
        long quotient = 0;
        long stepsize = 1;
        
        while (dividend >= divisor) {
            dividend -=  divisor;
            quotient += stepsize;
            divisor <<= 1;  //double the divisor
            stepsize <<= 1; //and double the stepsize
            if (quotient >= std::numeric_limits<int>::max()) return std::numeric_limits<int>::max(); 
        }
        if (stepsize == 1 || dividend == 0) {
            return quotient;
        } else {
            long recurseQuot = dividePrime(dividend, deno);    //re-start with step size 1!
            if (recurseQuot >= std::numeric_limits<int>::max()) return std::numeric_limits<int>::max();
            return (quotient + recurseQuot);
        }
    }
public:
    int divide(int nume, int deno) {
        if (deno == 0) return std::numeric_limits<int>::max(); //divide by 0 case!
        if (deno == 1) return nume;                            //trivial optimization
        if (nume == 0) return 0;                               //trivial optimization
        
        bool positiveResult = ((nume >= 0 && deno > 0) || (nume < 0 && deno < 0));
        long dividend = abs((long)nume);
        long divisor  = abs((long)deno);

        long quotient = dividePrime(dividend, divisor);
        return (positiveResult ? quotient : -1 * quotient);
    }
};
