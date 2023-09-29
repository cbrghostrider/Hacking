class Solution {
public:
    
    // find leftmost index of target
    int findLeftIndex(const vector<int>& nums, int target, int left, int right) {
        if (right - left <= 1) {
            if (nums[left] == target) {
                return left;
            }
            if (nums[right] == target) {
                return right;
            }
            return -1;
        }
        
        int mid = ((long long)left + right)/2;
        if (nums[mid-1] >= target) {
            return findLeftIndex(nums, target, left, mid-1);
        }
        if (nums[mid] == target) {
            return mid;
        }
        return findLeftIndex(nums, target, mid+1, right);
        
    }
    
    // find rightmost index of target
    int findRightIndex(const vector<int>& nums, int target, int left, int right) {
        if (right - left <= 1) {
            if (nums[right] == target) {
                return right;
            }
            if (nums[left] == target) {
                return left;
            }
            return -1;
        }
        
        int mid = ((long long)left + right)/2;
        if (nums[mid+1] <= target) {
            return findRightIndex(nums, target, mid+1, right);
        }
        if (nums[mid] == target) {
            return mid;
        }
        return findRightIndex(nums, target, left, mid-1);
    }
    
    bool isMajorityElement(vector<int>& nums, int target) {
        int left = findLeftIndex(nums, target, 0, nums.size()-1);
        int right = findRightIndex(nums, target, 0, nums.size()-1);
        if (left == -1 || right == -1) {
            return false;
        }
        int occurrences = right-left+1;
        if (occurrences > nums.size()/2) {
            return true;
        }
        return false;
    }
};
