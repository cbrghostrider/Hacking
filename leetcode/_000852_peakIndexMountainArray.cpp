class Solution {
public:
    
    // Termination conditions are 3 and 4 sized arrays.
    // Looking at mid, and at numbers just before and after it, we can decide whether
    // that part is trending up still or trending down.
    // Accordingly we recurse in the left or right halves.
    int findPeak(const vector<int>& nums, int left, int right) {
        if (right - left <= 3) {
            int max = nums[left];
            int maxInd = left;
            for (int i = left+1; i<=right; i++) {
                if (max < nums[i]) {
                    max = nums[i];
                    maxInd = i;
                }
            }
            return maxInd;
        }
        
        int mid = ((long long)left + right)/2;
        
        if (nums[mid-1] < nums[mid] && nums[mid] < nums[mid+1]) {  // uptrending at mid
            return findPeak(nums, mid, right);
        } else if (nums[mid-1] > nums[mid] && nums[mid] > nums[mid+1]) {  // downtrending at mid
            return findPeak(nums, left, mid);
        }
        return mid;
    }
    
    int peakIndexInMountainArray(vector<int>& arr) {
        return findPeak(arr, 0, arr.size()-1);
    }
};
