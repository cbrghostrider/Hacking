class Solution {
    // sort the array first in increasing order
    //
    // Let dp(i) = (val_i, val_i_prime) denote the MAX points gained considering numbers up to index i
    //    val_i = MAX points gotten, assuming we selected this number
    //    val_i_prime = MAX points gotten, assuming we de-selected this number
    //
    //  in_seq = true if num_i is in sequence after num_i-1
    //  val_i_prime = max(dp[i-1].val_i, dp[i-1].val_i_prime)
    //  val_i = num_i * freq_i + (in_seq ? dp[i-1].val_i_prime : val_i_prime)
    // 
    // now keep building this array up to the end, and we have our final answer.
    // which is max of (val_n, val_n_prime).
public:
    // O(n log n) time, O(n) space DP solution.
    // space can be optimized to O(1) because we only need to keep prev dp.
    int deleteAndEarn(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        
        unordered_map<int, int> freqs;
        for (int n: nums) {freqs[n]++;}
        if (freqs.size() == 1) return (nums[0] * freqs[nums[0]]);
        
        // sorted on vals
        vector<pair<int, int>> sfreqs(freqs.begin(), freqs.end());
        std::sort(sfreqs.begin(), sfreqs.end(), [](const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
            return lhs.first < rhs.first;
        });
        
        // max points up to curr index, assuming we:
        // (select this index, deselect this index)
        vector<pair<int, int>> dp(sfreqs.size(), {0, 0});  
        
        // Base cases, i=0, i=1
        dp[0] = {sfreqs[0].first * sfreqs[0].second, 0};
        if (sfreqs[1].first == sfreqs[0].first + 1) {
            dp[1].first = sfreqs[1].first * sfreqs[1].second + dp[0].second;
            dp[1].second = std::max(dp[0].first, dp[0].second);
        } else {
            dp[1].second = std::max(dp[0].first, dp[0].second);
            dp[1].first = sfreqs[1].first * sfreqs[1].second + dp[1].second;
        }
        
        // DP.
        for (int i=2; i<sfreqs.size(); i++) {
            const bool in_seq = sfreqs[i].first == sfreqs[i-1].first + 1;
            dp[i].second = std::max(dp[i-1].first, dp[i-1].second);
            dp[i].first = sfreqs[i].first * sfreqs[i].second + (in_seq ? dp[i-1].second : dp[i].second);
        }
        return std::max(dp[sfreqs.size()-1].first, dp[sfreqs.size()-1].second);
    }
};
