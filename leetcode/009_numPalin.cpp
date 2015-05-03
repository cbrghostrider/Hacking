class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        
        long bigDiv = 1;
        int num = x;
        while (num) {
            bigDiv *= 10;
            num /= 10;
        }
        bigDiv /= 10;
        
        long smallDiv = 1;
        while (bigDiv >= smallDiv) {
            int upperEnd = ((long)x / bigDiv) % 10;
            int lowerEnd = ((long)x / smallDiv) % 10;
            if (upperEnd != lowerEnd) {
                return false;
            }
            bigDiv   /= 10;
            smallDiv *= 10;
        }
        return true;
    }
};
