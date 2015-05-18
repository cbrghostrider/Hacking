class Solution {
public:
    string convertToTitle(int n) {
        if (n <= 0) return "";
        if (n < 26) {
            return string (1, n - 1 + 'A');
        } else if ((n % 26) == 0) {
            return (convertToTitle(n/26 - 1) + "Z");
        }
        return (convertToTitle(n/26) + convertToTitle(n%26));
    }
};
