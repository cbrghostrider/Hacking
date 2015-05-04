class Solution {
public:
    //since no two adjacent elements are the same, function is *wavy*
    //therefore by looking at midpoint, and seeing if the function is increasing or decreasing there
    //we can reduce half the search space at each step w/ binary search

    bool isPeakElement(vector<int>& nums, int i) {
        bool evalPrev = (i == 0)                 || (nums[i] > nums[i-1]);
        bool evalNext = (i == (nums.size() - 1)) || (nums[i] > nums[i+1]);
        if (evalPrev && evalNext) return true ; else return false;
    }
    
    int binarySearchPeak(vector<int>& nums, int lb, int ub) {
        if ((lb == ub) || ((lb + 1) == ub)) { //base cases
            if (isPeakElement(nums, lb)) {
                return lb;
            } else if (isPeakElement(nums, ub)) {
                return ub;
            }
            return -1;
        }
        int mid = (lb + ub)/2;
        if (isPeakElement(nums, mid)) {
            return mid;
        } else if (nums[mid] < nums[mid+1]) {
            return binarySearchPeak(nums, mid, ub);
        } else {
            return binarySearchPeak(nums, lb, mid);
        }
    }
    
    int findPeakElement(vector<int>& nums) {
        if (nums.size() == 0) {
            return -1; //undefined
        } 
        
        //cover cases at extremes
        if (isPeakElement(nums, 0)) {
            return 0;
        } else if (isPeakElement(nums, nums.size() - 1)) {
            return (nums.size() - 1);
        }
        
        return binarySearchPeak(nums, 0, nums.size() - 1);
    }
};
