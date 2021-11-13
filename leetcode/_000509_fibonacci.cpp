class Solution {
public:
    int fib(int n) {
        if (n == 0 || n == 1) return n;
        int fi=0, fj=1;
        for (int i=2; i<=n; i++) {
            int fk = fi+fj;
            fi = fj;
            fj = fk;
        }
        return fj;
    }
};
