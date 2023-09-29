class Solution {
    bool isFirstGE(const vector<int>& nums, int k, int a1, int a2) {
        for (int i=0; i<k; i++) {
            if (nums[a1 + i] < nums[a2 + i]) return false;
            else if (nums[a1 + i] > nums[a2 + i]) return true;
        }
        return true;
    }
 public:
    // O(n * k) time, O(1) space.
    vector<int> largestSubarray(vector<int>& nums, int k) {
        int largest_start = 0;
        for (int start=1; start<=nums.size()-k; start++) {
            if (!isFirstGE(nums, k, largest_start, start)) {
                largest_start = start;
            }
        }
        vector<int> ans(k, 0);
        for (int i=0; i<k; i++) ans[i] = nums[largest_start+i];
        return ans;
    }
};
