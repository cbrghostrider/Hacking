class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n < 1 || n == 2) return false;
        if (n == 1) return true;
        long nl = (long)n, test=3;
        while (test <= nl) {
            if (test == nl) return true;
            test *= 3;
        }
        return false;
    }
};
