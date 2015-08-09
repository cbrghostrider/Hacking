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
    vector<int> majorityElement(vector<int>& nums) {
        if (nums.size() <=1) { return nums;}
        if (nums.size() == 2) {
            if (nums[0] == nums[1]) return vector<int>(1, nums[0]);
            else return nums;
        }
        int n = nums.size();
        int posnby3  = n/3   + ((n%3) ? 1 : 0);
        int posn2by3 = 2*n/3 + (((2*n)%3) ? 1 : 0);
        int nby3  = quickSelect(nums, 0, nums.size()-1, posnby3 - 1);
        int n2by3 = quickSelect(nums, 0, nums.size()-1, posn2by3 - 1);
        int cnby3  = std::count(nums.begin(), nums.end(), nby3);
        int cn2by3 = std::count(nums.begin(), nums.end(), n2by3);
        vector<int> retval;
        if (cnby3 > (nums.size()/3)) { retval.push_back(nby3);}
        if (cn2by3 > (nums.size()/3) && nby3 != n2by3) { retval.push_back(n2by3);}
        return retval;
    }
};
