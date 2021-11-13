class Solution {
public:
    int tribonacci(int n) {
        if (n == 0) return 0;
        if (n <= 2) return 1;
        int ti=0, tj=1, tk=1;
        for (int c=3; c<=n; c++) {
            int temp = ti+tj+tk;
            ti=tj;
            tj=tk;
            tk=temp;
        }
        return tk;
    }
};
