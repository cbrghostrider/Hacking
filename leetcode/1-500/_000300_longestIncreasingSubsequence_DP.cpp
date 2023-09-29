class Solution {
    struct Info {
        int lis_not_me = 0;  // LIS from before, not ending in me
        int lis_me = 0;      // LIS ending in me
    };
public:
    // O(n^2) time, O(n) space.
    int lengthOfLIS(vector<int>& nums) {
        vector<Info> dp(nums.size(), Info());

        // Base case.
        dp[0] = {0, 1};
        
        // DP.
        for (int i=1; i<nums.size(); i++) {
            Info my_info;
            my_info.lis_not_me = std::max(dp[i-1].lis_not_me, dp[i-1].lis_me);            
            
            int len=0;
            for (int j=i-1; j>=0; j--) {
                if (nums[j] >= nums[i]) continue;
                len = std::max(len, dp[j].lis_me);
            }
            my_info.lis_me = len+1;
            dp[i] = my_info;
        }
        
        const Info& inf = dp[nums.size()-1];
        return std::max(inf.lis_not_me, inf.lis_me);
    }
};
