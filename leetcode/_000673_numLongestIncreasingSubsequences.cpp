class Solution {
    struct Info {
        int lis_me_count=0;
        int lis_me=0;      
    };
public:
    // O(n^2) time, O(n) space.
    int findNumberOfLIS(vector<int>& nums) {
        vector<Info> dp(nums.size(), Info());        
        
        // Base case.
        dp[0] = {1, 1};
        
        int best_size=1;
        int best_count=1;
        
        for (int i=1; i<nums.size(); i++) {            
            int my_best=1;
            int my_best_count=1;
            for (int j=i-1; j>=0; j--) {
                if (nums[j] < nums[i] && dp[j].lis_me + 1 > my_best) {
                    my_best = dp[j].lis_me + 1;
                    my_best_count = dp[j].lis_me_count;
                } else if (nums[j] < nums[i] && dp[j].lis_me + 1 == my_best) {
                    my_best_count += dp[j].lis_me_count;
                }
            }
            dp[i].lis_me = my_best;
            dp[i].lis_me_count = my_best_count;
            if (my_best > best_size) {
                best_size = my_best;
                best_count = my_best_count;
            } else if (my_best == best_size) {
                best_count += my_best_count;
            }
        }
        return best_count;
    }
};
