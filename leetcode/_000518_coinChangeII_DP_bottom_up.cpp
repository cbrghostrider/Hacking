class Solution {
    // Let change(x, i) represent the amount of ways to make x in change, using only coins from index 0...i
    // 
    // Recurrence:
    // change(x, i) = ways
    // 
    //    let n = x/coins[i] = max number of coins used to make amount <x
    // 
    //    ways = 0
    //    for k=0 to n   // taking 0 to n coins of denomination 
    //       new_ways = change(x - k*coins[i], i-1)
    //       ways += new_ways
public:
    // O(m * n * n): m = |amount|, n = |coins|
    int change(int amount, vector<int>& coins) {
        std::sort(coins.begin(), coins.end());
        
        vector<vector<int>> dp(amount+1, vector<int>(coins.size(), 0));
        
        // Base case, take only the 0th index coin.
        int max_0 = amount/coins[0];
        for (int k=0; k<=max_0; k++) {
            int my_money = k*coins[0];
            dp[my_money][0] = 1;
        }
        
        // DP.
        for (int i=1; i<coins.size(); i++) {
            for (int x=0; x<=amount; x++) {
                int n = x/coins[i];
                int ways = 0;
                for (int k=0; k<=n; k++) {
                    int my_money = k * coins[i];   // money exclusively due to new coin: coins[i]
                    if (my_money > x) continue;
                    int leftover = x - my_money;
                    ways += dp[leftover][i-1];
                }
                dp[x][i] = ways;
            }
        }
        
        return dp[amount][coins.size()-1];
    }
};
