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
