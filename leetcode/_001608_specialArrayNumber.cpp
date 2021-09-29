class Solution {
public:
    // counts how many numbers are greater than or equal to val (within [left, right]).
    int howManyGE(const vector<int>& nums, int val, int left, int right) {
        if (right - left <= 1) {
            int count = 0;
            if (nums[left] >= val) count++;
            if (nums[right] >= val && right != left) count++;
            return count;
        }
        
        int mid = ((long long)left + right) / 2;
        if (nums[mid-1] >= val) {
            return howManyGE(nums, val, left, mid-1) + 1 + (right - mid);
        } else if (nums[mid] >= val) {
            return 1 + right - mid;
        }
        return howManyGE(nums, val, mid+1, right);
    }
    
    // nlogn
    int specialArray(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        
        int last_candidate = nums.size();
        for (int candidate = 0; candidate <= last_candidate; candidate++) {
            int count = howManyGE(nums, candidate, 0, nums.size()-1);
            if (count == candidate) {
                return candidate;
            }
        }
        return -1;
    }
};
