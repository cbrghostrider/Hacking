// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    vector<int> binarySearchRange(vector<int>& nums, int target, int lo, int hi) {
        vector<int> retval;
        if (nums[lo] == target && nums[hi] == target) {
            retval.push_back(lo);
            retval.push_back(hi);
            return retval;
        }
        if (lo == hi) {
            if (nums[lo] == target) {
                retval.push_back(lo);
                retval.push_back(hi);
            } else {
                retval.push_back(-1);
                retval.push_back(-1);
            }
            return retval;
        }
        int mid = (lo + hi)/2;
        int midplus = mid + 1;
        vector<int> lhs, rhs;
        if (nums[lo] <= target && nums[mid] >= target) {
            lhs = binarySearchRange(nums, target, lo, mid);
        }    
        if (nums[midplus] <= target && nums[hi] >= target) {
            rhs = binarySearchRange(nums, target, midplus, hi);
        }
        if (!lhs.empty() && !rhs.empty()) {
            retval.push_back(lhs[0]);
            retval.push_back(rhs[1]);
            return retval;
        } else if (!lhs.empty()) {
            return lhs;
        } else if (!rhs.empty()) {
            return rhs;
        }
        retval.push_back(-1);
        retval.push_back(-1);
        return retval;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return binarySearchRange(nums, target, 0, nums.size()-1);
    }
};
