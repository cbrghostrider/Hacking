// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> retval;
        if (nums.size() == 0) {
            if (lower == upper) {
                return vector<string>(1, to_string(lower));
            } else {
                return vector<string>(1, to_string(lower) + "->" + to_string(upper));
            }
        }
        if (lower != nums[0]) {
            string latter = (lower+1 == nums[0]) ? "" : "->" + to_string(nums[0] - 1) ;
            retval.push_back(to_string(lower) + latter);
        }
        
        int expect = nums[0] + 1;
        string cur;
        for (int i=1; i<nums.size(); i++) {
            if (nums[i] == expect) {
                expect++;
                continue;
            } else {
                cur = to_string(nums[i-1]+1);
                if (nums[i] == nums[i-1]+2) {
                    retval.push_back(cur);
                } else {
                    retval.push_back(cur + "->" + to_string(nums[i]-1));
                }
                expect = nums[i] + 1;
            }
        }
        if (lower != upper && upper != nums[nums.size()-1]) {
            string former = (upper-1 == nums[nums.size()-1]) ? "" : to_string(nums[nums.size()-1] + 1) + "->";
            retval.push_back(former + to_string(upper));
        }
        return retval;
    }
};
