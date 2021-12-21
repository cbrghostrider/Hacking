class Solution {
    vector<int> perfect_squares;
    
    // (sig, least num)
    unordered_map<int, int> cache;
    
    void genSquares(int n) {
        int i=1;
        do {
            perfect_squares.push_back(i*i);
            i++;
        } while (i*i <= n);        
    }
    
    int signature(int index, int val) {
        return ((index << 16) | (val));
    }
    
    // considering numbers from indices [0...index] in perfect_squares
    // what are the least number that sum to val
    int leastNum(int index, int val) {
        int sig = signature(index, val);
        if (cache.find(sig) != cache.end()) return cache[sig];
        if (index == 0) {cache[sig] = val; return val;}
        
        int least=std::numeric_limits<int>::max();
        int div = val / perfect_squares[index];
        
        // Try all combos from taking 0 to div values of perfect_squares[index]
        for (int count=0; count <= div; count++) {
            int consumed = count * perfect_squares[index];
            int new_val = val - consumed;
            int recurse = leastNum(index - 1, new_val);
            int my_least = count + recurse;
            if (my_least < least) {least = my_least;}
        }
        
        cache[sig] = least;
        return cache[sig];
    }
    
public:
    int numSquares_(int n) {        
        genSquares(n);
        int num = leastNum(perfect_squares.size()-1, n);
        return num;
    }
    
    // 2D DP; inefficient.
    int numSquares__(int n) {        
        genSquares(n);
        
        vector<vector<int>> dp(perfect_squares.size(), vector<int>(n+1, 0));
        
        for (int ni=0; ni<=n; ni++) {
            dp[0][ni] = ni;
        }
        
        for (int i=1; i<perfect_squares.size(); i++) {
            for (int ni=1; ni<=n; ni++) {
                int this_sq = perfect_squares[i];
                int div = ni/this_sq;
                int least = std::numeric_limits<int>::max();
                for (int c=0; c<=div; c++) {
                    int consumed = c * this_sq;
                    int new_ni = ni - consumed;
                    int recurse = dp[i-1][new_ni];
                    int my_least = c + recurse;
                    if (my_least < least) {least = my_least;}
                }
                dp[i][ni] = least;
            }
        }
        
        return dp[perfect_squares.size()-1][n];
    }
   
    // 1-D DP. 
    // O(n * sqrt(n)) time, O(n) space.
    int numSquares(int n) {  
        genSquares(n);
        
        vector<int> dp(n+1, std::numeric_limits<int>::max());
        dp[0] = 0; dp[1] = 1;
        
        for (int ni=2; ni<=n; ni++) {
            for (int i=0; i<perfect_squares.size(); i++) {
                if (perfect_squares[i] > ni) break;
                // either take 1 coin of this deno now, and look in cache for how many of other amount
                // or take no coin of this deno now, and stay at current dp 
                dp[ni] = std::min(dp[ni], dp[ni - perfect_squares[i]] + 1);
            }
        }
        return dp[n];
    }
};
