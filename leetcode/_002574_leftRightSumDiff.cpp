class Solution {
public:
    vector<int> leftRigthDifference(vector<int>& nums) {
        vector<int> ans(nums.size(), 0);
        int total=0;
        for (int n : nums) {
            total += n;
        }
        int prefix=0;
        for (int i=0; i<nums.size(); i++) {
            int l = prefix;
            int r = total - prefix - nums[i];
            ans[i] = std::abs(l - r);
            prefix += nums[i];
        }
        return ans;
    }
};