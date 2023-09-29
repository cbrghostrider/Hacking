class Solution {
public:
    // returns the factors of x (not including 1)
    // O(x) time
    set<int> factorsX(int x) {
        if (x == 1) return {};
        set<int> ans;
        for (int i=2; i<=x/2; i++) {
            if (x % i == 0) ans.insert(i);
        }
        ans.insert(x);
        return ans;
    }
    
    // O(n * x) time, where x is max value of card, n is number of cards.
    // O(n * x) space.
    bool hasGroupsSizeX(vector<int>& deck) {
        unordered_map<int, int> counts;
        unordered_map<int, set<int>> factors;
        
        bool all_same = true;
        for (int d : deck) { 
            counts[d]++; 
            if (d != deck[0]) all_same = false;
        }
        if (all_same) return (deck.size() > 1);
        
        for (const auto& kv : counts) {
            factors[kv.first] = factorsX(kv.second);
        }
        
        set<int> result, result2;
        bool init = false;
        for (const auto& kv : factors) {
            const auto& fs = kv.second;
            if (!init) {
                result = fs;
                init = true;
            } else {
                std::set_intersection(fs.begin(), fs.end(), result.begin(), result.end(),
                                      std::inserter(result2, result2.begin()));
                result = result2;
                result2.clear();
            }
        }
        return (!result.empty());
    }
};
