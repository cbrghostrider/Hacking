class Solution {
    // Scan the array from left to right, 
    // Note the places where the sort property is invalidated (i<j, but a[i] not <= a[j])
    // Find the first and last index of such invalidations (call them x, y)
    // Find the smallest and biggest numbers between indices x and y
    // if we sort all numbers between x and y, then the smallest will come first and the biggest last
    // HOWEVER this smallest might cause more invalidations w.r.t. indices before x
    // similarly for largest w.r.t. indices after y
    // so basically, scan forward from 0, to see where smallest would fit (call this index i)
    // scan backwards from end of the array to see where largest would fit (call this index j)
    // the span [i, j] is the continuous subarray we need to sort
public:
    // O(n) time, O(1) space.
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int left_inval_index=-1, right_inval_index=-1;        
        int last = nums[0] - 1;
        for (int i=0; i<nums.size(); i++) {
            if (last <= nums[i]) {
                last = nums[i];
                continue;
            }
            if (left_inval_index == -1) {left_inval_index = i;}
            right_inval_index = i;
            last = std::max(nums[i], last);
        }
        
        if (left_inval_index == -1) return 0;

        int smallest=std::numeric_limits<int>::max();
        int largest=std::numeric_limits<int>::min();
        for (int i=left_inval_index; i<=right_inval_index; i++) {
            smallest = std::min(smallest, nums[i]);
            largest  = std::max(largest,  nums[i]);
        }
        
        int lo=0, hi=nums.size()-1;
        while (lo < nums.size() && nums[lo] <= smallest && lo < left_inval_index) {
            lo++;
        }
        while (hi >= 0 && nums[hi] >= largest & hi > right_inval_index) {
            hi--;
        }
        return hi-lo+1;
    }
};
