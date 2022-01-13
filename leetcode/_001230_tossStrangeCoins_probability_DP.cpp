class Solution {
    // dp(i, t) = prob[i]*(dp(i+1, t-1)) + (1-prob[i])*(dp(i+1, t))
public:
    // O(n^2) time, O(n^2) space.
    // space can be optimized, since we only need i+1 of first index and t or t-1 of second index
    double probabilityOfHeads(vector<double>& prob, int target) {
        if (target > prob.size()) return 0.0;
        
        vector<vector<double>> dp(prob.size(), vector<double>(prob.size()+1, 0.0));
        
        // Base cases.
        dp[prob.size()-1][1] = prob[prob.size()-1];        
        
        double mult=1;
        for (int i=prob.size()-1; i>=0; i--) {
            mult *= (1-prob[i]);  // rolling tail at i
            dp[i][0] = mult;      // rolling all tails at i and beyond
        }
        
        // DP.
        for (int i=prob.size()-2; i>=0; i--) {
            for (int t=1; t<=prob.size(); t++) {
                dp[i][t] = prob[i] * dp[i+1][t-1] + (1-prob[i])*dp[i+1][t];                
            }
        }
        
        return dp[0][target];
    }
};
