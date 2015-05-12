class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1.0;
        if (n == 1) return x;
        if (n == std::numeric_limits<int>::min()) return (myPow(x, n + 1) / x);
        if (n < 0)  return (1/myPow(x, -1*n));
        
        //n can be expressed as a binary number: say: 0xb7b6b5b4b3b2b1b0
        //n can be written as (128*b7 + 64*b6 + 32*b5 + 16*b4 + 8*b3 + 4*b2 + 2*b1 + b0)
	//since x^(a+b+c) = x^a * x^b * x^c, therefore, 
        //x^n can be written as (x^(128*b7) * x^(64*b6) * x^(32*b5) * x^(16*b4) * x^(8*b3) * x^(4*b2) * x^(2*b1) * x^(1*b0))
        //i.e. at each step, first multiply result by x if bk is set (for k from 0->31)
        //                 , then multiply x by itself to get new x
	//                 
	//since n has log n bits in it, this makes it O(log n)
        double result = 1.0;
        while (n != 0) {
            if (n & 1) {
                result *= x;
            }
            x *= x;
            n >>= 1;
        }
        return result;
    }
};
