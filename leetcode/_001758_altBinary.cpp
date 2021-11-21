class Solution {
public:
    int minOperations(string s) {
        int ops0=0, ops1=0;
        char last = '1';
        for (char ch : s) {
            if (ch == last) {ops0++;}
            last = (last == '1' ? '0' : '1');
        }
        last = '0';
        for (char ch : s) {
            if (ch == last) {ops1++;}
            last = (last == '1' ? '0' : '1');
        }
        return std::min(ops0, ops1);
    }
};
