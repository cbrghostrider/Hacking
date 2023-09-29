// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    unordered_map<int, int> countFreq_; //(number, count)
public:
    int singleNumber(vector<int>& nums) {
        for (int& num : nums) {
            if (countFreq_.find(num) == countFreq_.end()) {
                countFreq_[num] = 1;
            } else {
                countFreq_[num] += 1;
            }
        }
        for (int & num : nums) {
            if (countFreq_[num] == 1) {
                return num;
            }
        }
        return -1;//ill-defined input
    }
};
