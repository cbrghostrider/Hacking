// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> result(digits.size(), 0);
        int carry = 1;
        for (int ctr=digits.size()-1; ctr>=0; ctr--) {
            int res = carry + digits[ctr];
            result[ctr] = res % 10;
            carry = res / 10;
        }
        if (carry) result.insert(result.begin(), 1);
        return result;
    }
};
