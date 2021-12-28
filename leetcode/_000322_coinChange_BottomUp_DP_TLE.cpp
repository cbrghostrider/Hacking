class Solution {
public:
    
    int coinChange(vector<int>& coins, int amount) {
        std::sort(coins.begin(), coins.end());
        
        vector<vector<int>> dp(coins.size(), vector<int>(amount+1, 0));
        
        // Base case.
        for (int a=1; a<=amount; a++) {
            if (a % coins[0] == 0) {dp[0][a] = a / coins[0];}
            else dp[0][a] = -1;
        }
        
        for (int c=1; c<coins.size(); c++) {
            for (int a=1; a<=amount; a++) {
                dp[c][a] = dp[c-1][a];                
                int max_num = a/coins[c];
                if (max_num == 0) continue;
                
                for (int i=max_num; i>=1; i--) {
                    int consumed = i * coins[c];
                    int remaining = a - consumed;
                    int recurse = dp[c][remaining];
                    if (recurse == -1) continue;
                    int my_coins = i + recurse;
                    
                    if (dp[c][a] == -1) { dp[c][a] = my_coins; }                        
                    else { dp[c][a] = std::min(dp[c][a], my_coins); }
                }
            }
        }
        return dp[coins.size()-1][amount];
    }
    
};
