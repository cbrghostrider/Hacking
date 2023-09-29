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

    // Out of curiosity, I also implemented this using top down DP instead of bottom up DP.
    //
    // Turns out, the top-down is significantly slower (but just barely accepted).
    // 1684 ms vs. 280 ms.
    //
    // This was counter intuitive to me, because I was guessing that the top-down process would 
    // ONLY COMPUTE those amounts it needed, instead of blindly computing all 
    // amounts from 0 to input amount, like the iterative bottom-up process does.
    //
    string signature(int amount, int ndenos) {
        return std::to_string(amount) + "-" + std::to_string(ndenos);
    }
    
    unordered_map<string, int> cache;
    
    // ndenos indicates how many denomations I can use (starting from index 0)
    int ways(int amount, vector<int>& coins, int ndenos) {
        string sig = signature(amount, ndenos);
        if (cache.find(sig) != cache.end()) return cache[sig];
        
        if (ndenos == 1) {
            cache[sig] = (amount % coins[0]) == 0 ? 1 : 0;
            return cache[sig];
        }
            
        int tot_ways = 0;
        
        // how many max coins of the last denomination can I use
        int index = ndenos-1;
        int max_coins = amount/coins[index];
        for (int k=0; k<=max_coins; k++) {
            int my_money = k*coins[index];
            int my_ways = ways(amount - my_money, coins, ndenos-1);
            tot_ways += my_ways;
        }
        
        cache[sig] = tot_ways;
        return tot_ways;
    }
    
    int change(int amount, vector<int>& coins) {
        std::sort(coins.begin(), coins.end());
        
        return ways(amount, coins, coins.size());
    }
};
