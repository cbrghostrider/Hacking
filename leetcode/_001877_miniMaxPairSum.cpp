class Solution {
public:
    int minPairSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int maxps=0;
        for (int i=0; i<nums.size(); i++) {
            int ps = nums[i] + nums[nums.size()-1-i];
            maxps = std::max(maxps, ps);
        }
        return maxps;
    }
};
