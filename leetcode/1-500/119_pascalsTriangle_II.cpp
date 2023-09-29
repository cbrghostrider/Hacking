// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex < 0) return vector<int>();
        if (rowIndex == 0) return vector<int>(1, 1);
        
        vector<int> prev = vector<int>(2, 1);
        for (int i=2; i<=rowIndex; i++) {
            vector<int> pas(prev.size() + 1, 1);
            for (int p=1; p < prev.size(); p++) {
                pas[p] = prev[p-1] + prev[p];
            }
            prev = pas;
        }
        return prev;
    }
};

