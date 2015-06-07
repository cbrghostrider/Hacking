// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    int binarySearchPosition(vector<int>& nums, int target, int lo, int hi) {
        if (lo == hi) {
            if (nums[lo] >= target) {
                return lo;
            } else {// (nums[lo] < target)
                return (lo+1);
            }
        } else if (nums[lo] >= target) {
            return lo;
        } else if (nums[hi] == target) {
            return hi;
        } else if (nums[hi] < target) {
            return (hi+1);
        }
        int mid = (lo + hi)/2;
        int midplus = mid + 1;
        if (nums[lo] <= target && nums[mid] >= target) {
            return binarySearchPosition(nums, target, lo, mid);
        } else if (nums[midplus] <= target && nums[hi] >= target) {
            return binarySearchPosition(nums, target, midplus, hi);
        }
        return mid+1; //number lies between mid and midplus
    }
public:
    int searchInsert(vector<int>& nums, int target) {
        if (nums.size() == 0) return -1;
        return binarySearchPosition(nums, target, 0, nums.size()-1);
    }
};
