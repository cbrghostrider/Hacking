class Solution {
public:
    int searchInternal(const vector<int>& nums, int left, int right, int target) {
        if (right - left <= 1) {
            if (nums[left] == target) {
                return left;
            } else if (nums[right] == target) {
                return right;
            }
            return -1;
        }
        
        int mid = ((long long)left + right)/2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] > target) {
            return searchInternal(nums, left, mid, target);
        }
        return searchInternal(nums, mid, right, target);
    }
    
    int search(vector<int>& nums, int target) {
        return searchInternal(nums, 0, nums.size()-1, target);
    }
};
