class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int result = m & n;
        int power_of_two = 1;

        while (power_of_two != 0) {
            if ((n - m) > power_of_two) {
                // if difference is sufficiently large, at some point, 
                // this power of two bit will be flipped
                result &= (~power_of_two);
            }
            power_of_two <<= 1;
        }
        return result;
    }
};

