class Solution {
public:
    int reverse(int x) {
        bool isNeg = (x < 0);
        long num = isNeg ? x*(-1) : x;
        
        long retAbs=0;
        while (num) {
            retAbs = retAbs*10 + (num % 10);
            num = num / 10;
        }
        
        int ret = retAbs;
        if (ret != retAbs) {
            return 0; //overflow
        }
        
        return (isNeg ? ret * (-1) : ret);
    }
};
