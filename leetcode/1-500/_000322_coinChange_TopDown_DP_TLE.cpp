class Solution {
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
    int coinChange(vector<int>& coins, int amount) {
        std::sort(coins.begin(), coins.end());
        int n = minNumber(coins, coins.size()-1, amount);
        return n;
    }
};
