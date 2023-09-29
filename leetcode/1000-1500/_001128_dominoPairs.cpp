class Solution {
public:
    // O(n^2) time, O(1) space.
    // Time limit exceeded.
    int numEquivDominoPairs2(vector<vector<int>>& dominoes) {
        int ans = 0;
        for (int i=0; i<dominoes.size(); i++) {
            for (int j=i+1; j<dominoes.size(); j++) {
                if (dominoes[i][0] == dominoes[j][0] && dominoes[i][1] == dominoes[j][1]) {
                    ans++;
                } else if (dominoes[i][0] == dominoes[j][1] && dominoes[i][1] == dominoes[j][0]) {
                    ans++;
                }
            }
        }
        return ans;
    }
    
    // O(n) time, O(n) space
    long makeDomino(int n1, int n2) {
        return (((long)n1 << 32) | n2);
    }
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        std::unordered_map<long, int> counts;
        vector<int>& last = dominoes[dominoes.size()-1];
        counts[makeDomino(last[0], last[1])]++;
        
        int ans = 0;
        for (int i=dominoes.size()-2; i>=0; i--) {
            vector<int>& d = dominoes[i];
            ans += counts[makeDomino(d[0], d[1])];
            if (d[0] != d[1]) ans += counts[makeDomino(d[1], d[0])];
            counts[makeDomino(d[0], d[1])]++;
        }
        return ans;
    }
};
