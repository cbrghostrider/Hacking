// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(n log n) complexity
// Note: Easy to use just std::binary_search
//
class Solution {
    bool binarySearch(const vector<int>& nums, int lo, int hi, int target) {
        if (lo == hi) {
            return (target == nums[lo]);
        }
        int mid = (lo + hi)/2;
        int midplus = mid+1;
        if (target == nums[mid] || target == nums[midplus]) return true;
        if (target < nums[mid]) return binarySearch(nums, lo, mid, target);
        return binarySearch(nums, midplus, hi, target);
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (int i=0; i<matrix.size(); i++) {
            if (matrix[i][0] > target) return false;
            //if (std::binary_search(matrix[i].begin(), matrix[i].end(), target)) {
            if (binarySearch(matrix[i], 0, matrix[i].size() - 1, target)) {
                return true;
            }
        }
        return false;
    }
};
