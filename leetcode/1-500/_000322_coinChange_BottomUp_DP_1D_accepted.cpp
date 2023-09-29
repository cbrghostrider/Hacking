class Solution {
  public:    
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, std::numeric_limits<int>::max());
        dp[0] = 0;
        
        for (int a=1; a<=amount; a++) {
            for (int c=0; c<coins.size(); c++) {
                if (coins[c] <= a) {
                    int recurse = dp[a - coins[c]];
                    if (recurse == std::numeric_limits<int>::max()) continue;
                    dp[a] = std::min(dp[a], dp[a - coins[c]] + 1);
                }
            }
            
        }
        return dp[amount] == std::numeric_limits<int>::max() ? -1 : dp[amount];
    }
};
