class Solution {
    int binarySearch(vector<int>& nums, int val, int lo, int hi) {
        if (lo == hi) return (val == nums[lo] ? lo : -1);
        int mid = (lo + hi)/2;
        int midplus = mid+1;
        bool monoIncLhs = nums[lo] <= nums[mid];
        bool monoIncRhs = nums[midplus] <= nums[hi];
        
        if ((monoIncLhs && val >= nums[lo] && val <= nums[mid]) ||
            (!monoIncLhs && (val >= nums[lo] || val <= nums[mid]))) { //recurse on LHS
            return binarySearch(nums, val, lo, mid);
        } else if ((monoIncRhs && val >= nums[midplus] && val <= nums[hi]) ||
                   (!monoIncRhs && (val >= nums[midplus] || val <= nums[hi]))){ //recurse on RHS
            return binarySearch(nums, val, midplus, hi);
        }
        return -1;//else number not present
    }
public:
    int search(vector<int>& nums, int target) {
        return binarySearch(nums, target, 0, nums.size()-1);
    }
};
