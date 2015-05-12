class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1.0;
        if (n == 1) return x;
        if (n == std::numeric_limits<int>::min()) return (myPow(x, n + 1) / x);
        if (n < 0)  return (1/myPow(x, -1*n));
        double subPow = myPow(x, n/2); //divide and conquer
        return (subPow * subPow  * (n % 2 == 1 ? x : 1.0));
    }
};

