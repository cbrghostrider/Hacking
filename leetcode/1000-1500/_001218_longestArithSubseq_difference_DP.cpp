class Solution {
    // Let las(i) denote the longest arithmetic subsequence leading up to index i
    // such that it satisfies the arithmetic difference "k"
    //
    // assume there is a hashtable, keeping for each element seen so far, 
    //     the length of the max subsequence ending in that element
    //
    // Recurrence:
    // las(i) = max(las(i-1), 1+ht[nums[i] - k])
public:
    // O(n) time, O(n) space.
    int longestSubsequence(vector<int>& arr, int difference) {
        if (arr.size() == 0) return 0;
        
        unordered_map<int, int> ss_len;
        vector<int> dp(arr.size(), 0);
        
        // Base case.
        dp[0] = 1;
        ss_len[arr[0]] = 1;
        
        // DP.
        for (int i=1; i<arr.size(); i++) {
            int c1 = dp[i-1];
            int search = arr[i] - difference;
            int c2 = 1 + ss_len[search];
            
            dp[i] = std::max(c1, c2);
            ss_len[arr[i]] = std::max(ss_len[arr[i]], c2);
        }
        
        return dp.back();
    }
};
