// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------

class Solution {
public:
    int quickSelect(vector<int>& nums, int lo, int hi, int kth) {
        if (lo == hi) {
            assert(kth == lo);
            return (nums[lo]);
        }

        int pivotind = (rand() % (hi - lo + 1)) + lo;
        std::swap(nums[lo], nums[pivotind]);

        int lp = lo+1;
        int hp = hi;
        int pivot = nums[lo];

        while (lp <= hp) {
            while (nums[lp] <= pivot) lp++;
            while (nums[hp] > pivot) hp--;
            if (lp > hp) break;
            if (lp <= hi) {
                std::swap(nums[lp], nums[hp]);
                lp++; hp--;
            }
        }
        std::swap(nums[lo], nums[hp]);

        //hp is the pivot

        if (kth == hp) { return nums[hp]; }
        if (kth < hp) {
            return quickSelect(nums, lo, hp-1, kth);
        }
        return quickSelect(nums, hp+1, hi, kth);//(kth - (hp-lo+1)));
    }

    int findKthLargest(vector<int>& nums, int k) {
        srand(time(NULL));
        return quickSelect(nums, 0, nums.size()-1, nums.size()-k);
    }
};
