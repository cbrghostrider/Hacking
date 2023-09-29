// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    int quickSelect(vector<int>& nums, int lo, int hi, int kth) {
        if (lo == hi) {
            return nums[lo];
        }
        if (lo + 1 == hi) {
            int smaller = nums[lo] < nums[hi] ? nums[lo] : nums[hi];
            int larger  = nums[lo] > nums[hi] ? nums[lo] : nums[hi];
            return (kth == lo ? smaller : larger);
        }
        //CAUTION: Choosing first element as pivot is bad for sorted or reverse sorted data
        int pivot = nums[lo];
        int plhs=lo+1, prhs=hi;

        while (1) {
            while (nums[plhs] < pivot) {
                if (plhs == hi) break;
                plhs++;
            }
            while (nums[prhs] > nums[lo]) {
                if (prhs == lo) break;
                prhs--;
            }
            if (plhs >= prhs) break;
            std::swap(nums[plhs++], nums[prhs--]);
        }
        std::swap(nums[lo], nums[prhs]);
        if (kth == prhs) return nums[prhs];
        if (kth > prhs) return quickSelect(nums, prhs+1, hi, kth);
        return quickSelect(nums, lo, prhs-1, kth);
    }
public:
    int majorityElement(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        return (quickSelect(nums, 0, nums.size()-1, nums.size()/2));
    }
};
