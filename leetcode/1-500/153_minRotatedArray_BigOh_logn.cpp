// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    bool isMinElement(vector<int>& nums, int i) { //compared to both my neighbors, am I min
        bool evalPrev = (i == 0) ? (nums[i] <= nums[nums.size()-1]) : (nums[i] < nums[i-1]);
        bool evalNext = (i == (nums.size() - 1)) ? (nums[i] <= nums[0]) : (nums[i] < nums[i+1]);
        if (evalPrev && evalNext) return true ; else return false;
    }
    
    int binarySearchMinima(vector<int>& nums, int lb, int ub) {
        if ((lb == ub) || ((lb + 1) == ub)) { //base cases
            if (isMinElement(nums, lb)) {
                return nums[lb];
            } else if (isMinElement(nums, ub)) {
                return nums[ub];
            }
            return -1; // error?
        }
        int mid = (lb + ub)/2;
        if (isMinElement(nums, mid)) {
            return nums[mid];
        } else if (nums[mid] > nums[ub]) {
            return binarySearchMinima(nums, mid, ub);
        } else {
            return binarySearchMinima(nums, lb, mid);
        }
    }
    int findMin(vector<int>& nums) {
        if (nums.size() == 0) {
            return -1; //undefined
        }
        return binarySearchMinima(nums, 0, nums.size()-1);
    }
};
