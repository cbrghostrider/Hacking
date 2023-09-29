class Solution {
    int Q, M;
    int getCompat(const vector<int>& s, const vector<int>& m) {
        int score=0;
        for (int i=0; i<Q; i++) {
            if (s[i] == m[i]) score++;
        }
        return score;
    }
    void initialize(const vector<vector<int>>& students, const vector<vector<int>>& mentors) {
        for (int s=0; s<M; s++) {
            for (int m=0; m<M; m++) {
                compat[s][m] = getCompat(students[s], mentors[m]);
            }
        }
    }
    
    string signature(int n, const set<int>& ms) {
        string sig = "N:" + std::to_string(n);
        for (int m : ms) {
            sig += ":" + std::to_string(m);
        }
        return sig;
    }
    
    // Indices are: (student, mentor)
    vector<vector<int>> compat;
    
    // Cache used for top down dynamic programming.
    unordered_map<string, int> cache;
    
    
    // students numbered 0 through n-1 will get mentors chosen from mset.
    // maxCompat will return the max compatibility for the best pairing.
    // Note that mentors is purposely passed by value.
    // Top down dynamic programming.
    int maxCompat(int n, set<int> mset) {
        if (n == 0) {return 0;}
        
        string sig = signature(n, mset);
        if (cache.find(sig) != cache.end()) {return cache[sig];}
        
        int chosen=std::numeric_limits<int>::min();
        
        // Fix the last student's mentor, and recursively solve.
        // student n-1 is fixed now
        for (int m : mset) {
            set<int> ms = mset;
            ms.erase(m);
            int score = compat[n-1][m] + maxCompat(n-1, ms);
            if (score > chosen) {chosen = score;}
        }
        
        cache[sig] = chosen;
        return chosen;
    }
public:
    
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        Q = students[0].size();
        M = students.size();
        
        compat = vector<vector<int>>(M, vector<int>(M, 0));
        initialize(students, mentors);
        
        set<int> mset;
        for (int i=0; i<M; i++) {mset.insert(i);}
        
        return maxCompat(M, mset);
    }
};
