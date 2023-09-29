class Solution {
public:
    // O(n) time, O(n) space (for answer).
    vector<int> minSubsequence(vector<int>& nums) {
        int total_sum = 0;
        for (int n : nums) { total_sum += n; }
        std::sort(nums.begin(), nums.end());
        int sum = 0;
        vector<int> ans;
        for (int i=nums.size()-1; i>=0; i--) {
            if (sum <= total_sum/2) {
                ans.push_back(nums[i]);
            } else {
                break;
            }
            sum += nums[i];
        }
        return ans;
    }
};
