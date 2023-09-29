class Solution {
    struct InOut {
        int in=0;   // money given to me
        int out=0;  // money I gave out
    };    
    
    unordered_map<string, int> cache;
    
    string signature(const vector<int>& nums) {
        string ret;
        for (int n : nums) {ret += to_string(n) + ":";}
        return ret;
    }
    string signature(const vector<int>& t, const vector<int>& g) {
        string ret;
        ret += signature(t) + "<-->" + signature(g);
        return ret;
    }
    
    int solve(vector<int> took, vector<int> gave) {
        if (took.empty() || gave.empty()) return 0; 
        
        std::sort(took.begin(), took.end(), std::greater<int>());
        std::sort(gave.begin(), gave.end(), std::greater<int>());
        
        while (!took.empty() && took.back() == 0) {took.pop_back();}
        while (!gave.empty() && gave.back() == 0) {gave.pop_back();}
        
        string sig = signature(took, gave);
        if (cache.find(sig) != cache.end()) {return cache[sig];}
        
        if (took.back() == gave.back()) {
            took.pop_back(); gave.pop_back();
            int ans = 1 + solve(took, gave);
            cache[sig] = ans;
            return ans;
        }
        
        bool took_greater=took.back() > gave.back();
        vector<int>& remove_arr = took_greater ? gave : took;
        vector<int>& other = took_greater ? took : gave;
        
        int removed = remove_arr.back(); remove_arr.pop_back();
        
        int best_count=std::numeric_limits<int>::max();
        
        for (int i=0; i<other.size(); i++) {
            other[i] -= removed;
            int my_count = 1 + solve(took, gave);
            best_count = std::min(best_count, my_count);
            other[i] += removed;
        }
        
        cache[sig] = best_count;
        return cache[sig];
    }
    
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, InOut> inouts;
        
        // record in/out transactions
        for (const vector<int>& tx : transactions) {
            inouts[tx[0]].out += tx[2];
            inouts[tx[1]].in  += tx[2];
        }
        
        
        vector<int> took, gave;
        for (const auto& kv : inouts) {
            if (kv.second.in > kv.second.out) {
                took.push_back(kv.second.in - kv.second.out);
            } else if (kv.second.in < kv.second.out) {
                gave.push_back(kv.second.out - kv.second.in);
            }
        }        
        
        int count = solve(took, gave);
        return count;

    }
};
