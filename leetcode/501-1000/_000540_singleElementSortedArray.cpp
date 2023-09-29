class Solution {
    int find(const vector<int>& nums, int lo, int hi) {
        if (lo == hi) { return nums[lo];}
        // lo+1 == hi: shouldn't ever be called with an even number of elems
        if (lo+2 == hi) {
            return (nums[lo+1] == nums[lo] ? nums[hi] : nums[lo]);
        }   
        int mid = (hi+lo)/2;
        if (nums[mid] != nums[mid-1] && nums[mid] != nums[mid+1]) {
            return nums[mid];
        }
        if (nums[mid] == nums[mid-1]) {
            int n = (mid-lo+1);
            if (n % 2 == 0) {
                return find(nums, mid+1, hi);
            } else {
                return find(nums, lo, mid-2);
            }
        }
        int n = (hi-mid+1);
        if (n%2 == 0) {
            return find(nums, lo, mid-1);
        }
        return find(nums, mid+2, hi);
    }
public:
    int singleNonDuplicate(vector<int>& nums) {
        return find(nums, 0, nums.size()-1);
    }
};
