class Leaderboard {
    unordered_map<int, int> scores;
public:
    Leaderboard() {
    }
    
    void addScore(int playerId, int score) {
        scores[playerId] += score;
    }
    
    int top(int K) {
        vector<int> s;
        for (const auto& kv : scores) {
            s.push_back(kv.second);
        }
        std::sort(s.begin(), s.end(), std::greater<int>());
        int total=0;
        for (int i=0; i<K; i++) {total += s[i];}
        return total;
    }
    
    void reset(int playerId) {
        scores[playerId] = 0;
    }
};

/**
 * Your Leaderboard object will be instantiated and called as such:
 * Leaderboard* obj = new Leaderboard();
 * obj->addScore(playerId,score);
 * int param_2 = obj->top(K);
 * obj->reset(playerId);
 */
