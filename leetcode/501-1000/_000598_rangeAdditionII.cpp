class Solution {
public:    
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        if (ops.size() == 0) return m*n;
        if (m == 0 || n == 0) return 0;
        
        long min_ai, min_bi;
        min_ai = min_bi = std::numeric_limits<int>::max();
        
        for (const vector<int>& v : ops) {
            int ai=v[0], bi=v[1];
            if (ai < min_ai) {min_ai = ai;}
            if (bi < min_bi) {min_bi = bi;}
        }
        return (min_ai) * (min_bi);
    }
};
