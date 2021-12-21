class Solution {
    enum State {
        EMPTY=0,   // can move to EMPTY or BUY
        BUY,       // can move to HOLD or SELL
        SELL,      // can move to COOLDOWN
        HOLD,      // can move to HOLD or SELL
        COOLDOWN,  // can move to BUY or EMPTY
        NUM_STATES
    };
    
public:
    // O(n) time, O(n) space.
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(NUM_STATES, 0));
        
        // Base case, dp[0][state]
        dp[0][EMPTY] = 0;
        dp[0][BUY] = -1 * prices[0];
        dp[0][SELL] = std::numeric_limits<int>::min();
        dp[0][HOLD] = std::numeric_limits<int>::min();
        dp[0][COOLDOWN] = std::numeric_limits<int>::min();
        
        // DP.
        for (int i=1; i<prices.size(); i++) {
            dp[i][EMPTY] = std::max(dp[i-1][COOLDOWN], dp[i-1][EMPTY]);
            dp[i][BUY] = -1* prices[i] + std::max(dp[i-1][COOLDOWN], dp[i-1][EMPTY]);
            dp[i][SELL] = prices[i] + std::max(dp[i-1][HOLD], dp[i-1][BUY]);
            dp[i][HOLD] = std::max(dp[i-1][BUY], dp[i-1][HOLD]);
            dp[i][COOLDOWN] = dp[i-1][SELL];
        }
        
        int n = prices.size()-1;
        int m1 = std::max(std::max(dp[n][EMPTY], dp[n][BUY]), std::max(dp[n][SELL], dp[n][HOLD]));
        return std::max(m1, dp[n][COOLDOWN]);
    }
};
