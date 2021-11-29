class Solution {
    enum State {
        BUY=0,     // had 0, will have 1
        HOLD=1,    // had 1, will have 1
        IGNORE=2,  // had 0, will have 0
        SELL=3     // had 1, will have 0
    };
public:
    // let profit(i, state) denote max profit that can be made up to index i sequence.
    // state records current decision (buy, hold, sell, ignore)
    // profit(i, buy) = std::max(profit(i-1, sell), profit(i-1, ignore)) - prices[i]
    // profit(i, ignore) = std::max(profit(i-1, sell), profit(i-1, ignore))
    // profit(i, sell) = std::max(profit(i-1, buy), profit(i-1, hold)) + prices[i] - tx_fee
    // profit(i, hold) = std::max(profit(i-1, buy), profit(i-1, hold))
    int maxProfit(vector<int>& prices, int fee) {
        if (prices.size() == 0) return 0;
        const int N=prices.size();
        vector<vector<int>> profit(prices.size(), vector<int>(4, 0));
        
        // Base case.
        profit[0][BUY] = profit[0][HOLD] = -1*prices[0];  // note that hold means you had 1, so we have to include it here
        profit[0][SELL] = profit[0][IGNORE] = 0;
        
        // DP.
        for (int i=1; i<N; i++) {
            profit[i][BUY] = std::max(profit[i-1][SELL], profit[i-1][IGNORE]) - prices[i];
            profit[i][IGNORE] = std::max(profit[i-1][SELL], profit[i-1][IGNORE]);
            profit[i][HOLD] = std::max(profit[i-1][BUY], profit[i-1][HOLD]);
            profit[i][SELL] = std::max(profit[i-1][BUY], profit[i-1][HOLD]) + prices[i] - fee;
        }
        
        return std::max(std::max(profit[N-1][BUY], profit[N-1][SELL]), 
                        std::max(profit[N-1][HOLD], profit[N-1][IGNORE]));
    }
};
