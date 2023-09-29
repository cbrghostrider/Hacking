class Solution {
    // Recurrence:
    // Let lcs(i, j) = longest common subsequence of str1[0..i] and str2[0..j]
    //
    // lcs(i, j) = 
    //   ---> if str1[i] == str2[j]
    //          =   1 + lcs(i-1, j-1)  
    //   ---> otherwise 
    //          =   max(lcs(i-1, j-1), lcs(i, j-1), lcs(i-1, j))
public:
    
    // O(mn) time, O(mn) space.
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), 0));
        
        // Base cases: dp[i][0] and dp[0][j]
        unordered_set<char> seen;
        for (int i=0; i<text1.size(); i++) {
            seen.insert(text1[i]);
            if (seen.find(text2[0]) != seen.end()) {dp[i][0] = 1;}
        }
        seen.clear();
        for (int j=0; j<text2.size(); j++) {
            seen.insert(text2[j]);
            if (seen.find(text1[0]) != seen.end()) {dp[0][j] = 1;}
        }
        
        // DP.
        for (int i=1; i<text1.size(); i++) {
            for (int j=1; j<text2.size(); j++) {
                if (text1[i] == text2[j]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                    continue;
                }
                int c1 = dp[i-1][j-1];
                int c2 = dp[i-1][j];
                int c3 = dp[i][j-1];
                dp[i][j] = std::max(c1, std::max(c2, c3));
            }
        }
        
        return dp[text1.size()-1][text2.size()-1];
    }
};
