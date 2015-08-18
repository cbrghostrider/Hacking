// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> retval;
        if (numbers.size() <= 1) return retval;
        
        int n1p=0, n2p=numbers.size()-1;
        while (n1p < n2p) {
            while (n1p < n2p && (numbers[n1p] + numbers[n2p]) > target) n2p--;
            if (numbers[n1p] + numbers[n2p] == target) {
                retval.push_back(n1p+1);
                retval.push_back(n2p+1);
                return retval;
            }
            n1p++;
        }
        return retval;
    }
};
