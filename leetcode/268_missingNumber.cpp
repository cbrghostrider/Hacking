// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int N = nums.size();
        int expect = (N)*(N+1)/2;
        int total = std::accumulate(nums.begin(), nums.end(), 0, [] (const int& acc, const int& x) -> int {return (acc+x);});
        return (expect - total);
    }
};
