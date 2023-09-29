// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
private:
    map<int, int> numMap_; //(number, how many times it occurred)
public:
    int singleNumber(vector<int>& nums) {
        for (const int& num : nums) {
            if (numMap_.find(num) != numMap_.end()) {
                numMap_[num] += 1;
            } else {
                numMap_[num] = 1;
            }
        }
        for (const int& num : nums) {
            if (numMap_[num] == 1) {
                return num;
            }
        }
        return -1; //ill-defined problem
    }
};
