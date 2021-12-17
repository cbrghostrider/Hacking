class Solution {
    
	// O(log n) time for binary search.
    int missing(const vector<int>& nums, int k, int lo, int hi) {
        if (lo == hi) {return nums[lo] + k;}
        if (lo+1 == hi) {
            int consumed = nums[hi] - nums[lo] - 1;
            if (consumed >= k) return nums[lo] + k;
            return nums[hi] + k-consumed;
        }
        
        int mid = (lo+hi)/2;
        
        int spots_left = mid-lo + 1;
        int nums_left = nums[mid] - nums[lo] + 1;
        int gaps_left = nums_left - spots_left;
        
        if (gaps_left >= k) {
            return missing(nums, k, lo, mid);
        }
        
        return missing(nums, k - gaps_left, mid, hi);
    }
    
public:
    int missingElement(vector<int>& nums, int k) {
        return missing(nums, k, 0, nums.size()-1);
    }
};
