class Solution {
public:
    int balancedStringSplit(string s) {
        if (s.size() <= 1) return 0;
        int count=0;
        int parity = 0;
        for (char ch : s) {
            if (ch == 'L') {parity--;} else {parity++;}
            if (parity == 0) {count++;}
        }
        return count;
    }
};
