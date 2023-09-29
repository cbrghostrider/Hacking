constexpr int AGE_MIN=1;
constexpr int AGE_MAX=120;

class Solution {
    vector<vector<bool>> cache;
    unordered_map<int, int> freqs;
    
    bool willXFriendY(int x, int y) {
        if (y > x) return false;
        if (y <= 0.5*x + 7) return false;
        return true;
    }
    
    void precompute() {
        cache = vector<vector<bool>>(121, vector<bool>(121, false));
        for (int x=AGE_MIN; x<=AGE_MAX; x++) {
            for (int y=AGE_MIN; y<=AGE_MAX; y++) {
                cache[x][y] = willXFriendY(x, y);
            }
        }
    }
    
public:
    int numFriendRequests(vector<int>& ages) {
        precompute();
        for (int a : ages) {freqs[a]++;}
        
        int requests = 0;
        for (const auto& kv_x : freqs) {
            for (const auto& kv_y : freqs) {
                int x = kv_x.first;
                int y = kv_y.first;
                bool x_friend_y = cache[x][y];
                if (x_friend_y) {
                    requests += freqs[x] * freqs[y];
                    
                    if (x == y) {  // can't friend self
                        requests -= freqs[x];
                    }
                }
            }
        }
        return requests;
    }
};
