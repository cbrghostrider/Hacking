class Solution {
public:
    // When we finish one complete rotation around the sectors, we can "forget" about it,
    // since those sectors are visited equally.
    // so basically, algorithm is:
    // Scan backwards for the very first number (f)
    // Every sector from f to the last number (l) is visited one more time.
    vector<int> mostVisited(int n, vector<int>& rounds) {
        vector<int> ans;
        int f = rounds[0];
        int l = rounds[rounds.size()-1];
        if (f <= l) {
            for (int i=f; i<=l; i++) {ans.push_back(i);}
            return ans;
        }
        for (int i=f; i<=n; i++) {ans.push_back(i);}
        for (int i=1; i<=l; i++) {ans.push_back(i);}
        std::sort(ans.begin(), ans.end());
        return ans;
    }
};
