class Solution {
    // Recurrence:
    // Let dp(i, n) denote number of possible combinations adding up to n,
    //     considering numbers up to index i
    // 
    // dp(i, n) = sum cands
    //    cands = take nums[i] from 0 to target/nums[i] times each
    //    cands(x) = dp(i-1, x)
    
    
public:
    long combinationSum4(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        
        vector<int> dp(target+1, 0);
        
        // base cases
        dp[0] = 1;
        
        // DP.
        for (int t=1; t<=target; t++) {
            long count=0;
            for (int c=0; c<nums.size(); c++) {
                if (nums[c] <= t) {
                    long my_count = dp[t-nums[c]];
                    count += my_count;
                }
            }
            dp[t] = count;
        }
        
        return dp[target];
    }    
};
