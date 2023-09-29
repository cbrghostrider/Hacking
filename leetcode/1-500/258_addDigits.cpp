// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int addDigits(int num) {
        string digs = to_string(num);
        while (digs.length() > 1) {
            num = 0;
            for (int i=0; i<digs.length(); i++) {
                num += digs[i] - '0';
            }
            digs = to_string(num);
        }
        return stoi(digs);
    }
};

