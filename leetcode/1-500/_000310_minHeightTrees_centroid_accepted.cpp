    int signature(int index, int amount) {
        return ((amount << 4) | (index));
    }
    
    // (signature -> min num)
    unordered_map<int, int> cache;
    
    // min number of coins to produce exactly amount
    // using no denomination more than indicated by index ([0...index] indices)
    int minNumber(const vector<int>& coins, int index, int amount) {
        int sig = signature(index, amount);
        if (cache.find(sig) != cache.end()) return cache[sig];
        
        if (index == 0) {
            int ans=-1;
            if (amount % coins[index] == 0) { ans = amount / coins[index];}
            cache[sig] = ans;
            return ans;
        }
        
        if (amount == 0) {
            cache[sig] = 0;
            return 0;
        }
        
        int number=std::numeric_limits<int>::max();
        
        int max_num = amount/coins[index];
        for (int c=0; c <= max_num; c++) {
            int consumed = c * coins[index];
            int remaining = amount - consumed;
            int recurse = minNumber(coins, index-1, remaining);
            if (recurse == -1) continue;
            int my_coins = c + recurse;
            number = std::min(number, my_coins);
        }
        
        cache[sig] = number == std::numeric_limits<int>::max() ? -1 : number;
        return cache[sig];
    }
    
public:
    int coinChange_(vector<int>& coins, int amount) {
        std::sort(coins.begin(), coins.end());
        int n = minNumber(coins, coins.size()-1, amount);
        return n;
    }
    
    int coinChange_2(vector<int>& coins, int amount) {
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
