class Solution {
    // Recurrence:
    // let dp(i, sz) denote the min cost of cuts between positions i and j (=i+sz) (i, j are indices in cuts)
    // let len(i, j) be the length of the stick between positions i and j (=i+sz) (i, j are indices in cuts)
    // 
    // dp(i, sz) = min over all k dp(i, subsz) + dp(k, sz-subsz) + len (i, j)
    //    where subsz = len of cuts subarray between i and k
    //             sz = len of cuts subarray between i and j
public:
    // O(k^3) time, O(k^2) space.
    // k = |cuts|
    int minCost(int n, vector<int>& cuts) {
        if (cuts.empty()) return 0;
        
        std::sort(cuts.begin(), cuts.end());
        if (cuts[0] != 0) {cuts.insert(cuts.begin(), 0);}
        if (cuts.back() != n) {cuts.push_back(n);}
        
        vector<vector<int>> dp(cuts.size(), vector<int>(cuts.size()+1, 0));
        
        // Base cases: sz==2
        for (int i=0, j=2; j<cuts.size(); i++, j++) {
            int len = cuts[j] - cuts[i];
            dp[i][2] = len;
        }
        
        // DP.
        // sz is size of cuts subarray, not size of sub-stick
        for (int sz=3; sz<cuts.size(); sz++) {
            for (int i=0; i<cuts.size()-sz; i++) {
                const int j=i+sz;
                int len = cuts[j] - cuts[i];
                int min_val = std::numeric_limits<int>::max();
                for (int k=i+1, subsz=1; k<=j-1; k++, subsz++) {
                    int my_val = dp[i][subsz] + dp[k][sz-subsz] + len;
                    min_val = std::min(min_val, my_val);
                }
                dp[i][sz] = min_val;
            }
        }
        return dp[0][cuts.size()-1];
    }
};
