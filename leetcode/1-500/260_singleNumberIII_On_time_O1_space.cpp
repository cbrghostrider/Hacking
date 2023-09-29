// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int num = 0;  //holds x^y at the end
        for (const int& n : nums) num ^= n;
        
        //since x and y are distinct, at least one bit is set in x^y
        //find last such bit
        int lastbitset = num & (-num);
        vector<int> ret = {0, 0};
        
        //divide up the original set into 2, with
        //set 1: the last bit set
        //set 2: the last bit unset
        //then xor the respective sets
        //all duplicates of a number will be in the same set, and
        //x and y fall in different sets
        //so we can extract both x and y
        for (const int& n : nums) {
            if (n & lastbitset) {
                ret[0] ^= n;
            } else {
                ret[1] ^= n;
            }
        }
        return ret;
    }
};
