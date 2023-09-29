// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//for shits and giggles- functional programmers will recognize a left fold
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        bool hold = false;  //whether I am holding stock, or waiting to buy
        int boughtAt = -1, last = prices[0]; 
        int profit = std::accumulate(prices.begin()+1, prices.end(), 0, [&hold, &last, &boughtAt] (const int& acc, const int& sp) -> int {
            int newprof=0;
            if (sp > last && !hold) {
                boughtAt = last; 
                hold = true;
            } else if (sp < last && hold) { 
                newprof = last - boughtAt; 
                hold = false;
            }
            last = sp;
            return acc + newprof;
        });
        if (hold) profit += last - boughtAt;
        return profit;
    }
};
