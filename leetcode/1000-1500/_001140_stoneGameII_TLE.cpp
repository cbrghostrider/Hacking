//
// Using Top-Down memoization based dynamic programming.
// In theory it is O(n^3).
//
class Solution {
    struct Result {
        int alice_has=0;
        int bob_has=0;
    };
public:    
    
    string signature(int index, int size, int m) {
        return (std::to_string(index) + "-" + std::to_string(size) + "-" + std::to_string(m));
    }
    
    std::unordered_map<string, Result> cache_alice_plays;
    std::unordered_map<string, Result> cache_bob_plays;
    vector<int> piles;
    vector<vector<int>> sum_piles;
    
    void compute_sum_piles(const vector<int>& piles, const int N) {
        sum_piles = vector<vector<int>>(N, vector<int>(N+1, 0));
        for (int i=0; i<N; i++) {
            sum_piles[i][1] = piles[i];
        }
        for (int sz=2; sz<=N; sz++) {
            for (int i=0; i<=N-sz; i++) {
                sum_piles[i][sz] = sum_piles[i+1][sz-1] + piles[i];
            }
        }
    }
    
    // Simulates a play, both Alice and Bob can get to this state, so we simulate accordingly.
    // We are at index "index", pile size is "size", m is current value at this step.
    Result play(int index, int size, int m, bool alice_plays) {
        if (size == 0) return {0, 0};
        if (size == 1) {
            if (alice_plays) {return {piles[index], 0};}
            else {return {0, piles[index]};}
        }
        
        string sig = signature(index, size, m);
        
        auto& cache = (alice_plays ? cache_alice_plays : cache_bob_plays);
        
        if (cache.find(sig) != cache.end()) return cache[sig];
        Result ans;
        
        if (alice_plays) {
            // Simulate Alice.
            int max_diff = std::numeric_limits<int>::min();           
            for (int x=1; x<=std::min(2*m, size); x++) {
                int new_m = std::max(x, m);
                Result result = play(index+x, size-x, new_m, false);
                int alice_has = sum_piles[index][x] + result.alice_has;
                int bob_has = result.bob_has;
                int diff = alice_has - bob_has;
                if (diff > max_diff) {
                    max_diff = diff;
                    ans = {alice_has, bob_has};
                }
            }
        } else {
            // Simulate Bob.
            int max_diff = std::numeric_limits<int>::min();
            for (int x=1; x<=std::min(2*m, size); x++) {
                int new_m = std::max(x, m);
                Result result = play(index+x, size-x, new_m, true);
                int alice_has = result.alice_has;
                int bob_has = sum_piles[index][x] + result.bob_has;
                int diff = bob_has - alice_has;
                if (diff > max_diff) {
                    max_diff = diff;
                    ans = {alice_has, bob_has};
                }
            }
        }
        cache[sig] = ans;
        return ans;
    }
    
    int stoneGameII(vector<int>& p) {
        piles = p;
        compute_sum_piles(piles, piles.size());
        Result result = play(0, piles.size(), 1, true);
        return result.alice_has;
    }
};
