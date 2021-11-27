class Solution {
public:
    // Let dp(i, j) be the minimum cost to make substrings s1.substr(i) and s2.substr(j) equal.
    // The answer to the problem is dp(s1.size()-1, s2.size()-1)
    // Recurrence:
    // dp(i, j) = 
    //   dp(i-1, j-1) ; if s1[i] == s2[j]
    //   min_cost     ; if s1[i] != s2[j]
    //   where, 
    //     min_cost = min(c1, c2, c3)
    //       c1 = s1[i] + dp(i-1, j)
    //       c2 = s2[j] + dp(i, j-1)
    //       c3 = s1[i] + s2[j] + dp(i-1, j-1)
    // O(M*N) time, O(M*N) space.
    int minimumDeleteSum(string s1, string s2) {
        if (s1.empty() && s2.empty()) return 0;
        const int N = s1.size(), M = s2.size();
        
        // cumulative sums are used to keep track of total cost of deleting everything up to index i.
        vector<int> csums1(s1.size(), 0), csums2(s2.size(), 0);
        int sum=0;
        for (int i=0; i<N; i++) {sum += s1[i]; csums1[i] = sum;}
        sum = 0;
        for (int i=0; i<M; i++) {sum += s2[i]; csums2[i] = sum;}
        
        if (s1.empty()) return csums2[s2.size()-1];
        if (s2.empty()) return csums1[s1.size()-1];
        
        vector<vector<int>> dp(N, vector<int>(M, 0));
        for (int i=0; i<N; i++) {
            for (int j=0; j<M; j++) {
                int dp_im1_jm1 = (i == 0 && j == 0 ? 0 : i == 0 ? csums2[j-1] : j == 0 ? csums1[i-1] : dp[i-1][j-1]);
                int dp_im1_j = (i == 0 ? csums2[j] : dp[i-1][j]);
                int dp_i_jm1 = (j == 0 ? csums1[i] : dp[i][j-1]);
                
                if (s1[i] == s2[j]) {
                    dp[i][j] = dp_im1_jm1;
                    continue;
                }
                int c1 = s1[i] + dp_im1_j;
                int c2 = s2[j] + dp_i_jm1;
                int c3 = s1[i] + s2[j] + dp_im1_jm1;
                dp[i][j] = std::min(std::min(c1, c2), c3);
            }
        }
        
        return dp[s1.size()-1][s2.size()-1];
    }
};
