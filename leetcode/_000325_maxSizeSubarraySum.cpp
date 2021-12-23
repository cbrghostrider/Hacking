class Solution {
public:
    // Recurrence:
    // Let dp(i) denote the max length of subarray that sums to k, up to index i
    //
    // dp(i) = max(c1, c2);
    //    c1 = dp(i-1)
    //    c2 = update sa_sum uo map, and find sa_sum(k) if it exists
    //
    // This solves assuming "subarray" is *not* a contiguous chunk.
    //
    // BUT IT SEEMS THEY WANT A CONTIGUOUS CHUNK SUBARRAY ONLY.
    // So this solution won't apply. Leaving it here because it is interesting.
    //
    // O(n^2) time, O(n) space.
    int maxSubArrayLen_(vector<int>& nums, int k) {
        // (sum, length): subarray sums
        // the max length of subarray that sums to "sum"
        // at any iteration i this is updated taking into account the new element
        unordered_map<int, int> sa_sum;
        vector<int> dp(nums.size(), 0);
        
        // Base case.
        dp[0] = nums[0] == k ? 1 : 0;
        sa_sum[nums[0]] = 1;
            
        // DP.
        for (int i=1; i<nums.size(); i++) {
            int c1 = dp[i-1];
            unordered_map<int, int> my_map;
            my_map[nums[i]] = 1;
            for (const auto& kv : sa_sum) {
                int key = nums[i] + kv.first;
                my_map[key] = std::max(1+kv.second, sa_sum[key]);
            }
            std::swap(my_map, sa_sum);
            int c2 = sa_sum[k];
            dp[i] = std::max(c1, c2);
        }
        
        return dp[nums.size()-1];
    }
    
    // This solution solves the actual problem.
    // O(n) time, O(n) space.
    int maxSubArrayLen(vector<int>& nums, int k) {       
        // (x -> i)
        // The latest index that sums up to "x".
        // The earliest index that sums up to "x".
        unordered_map<int, int> latest, earliest;
        int sum=0;
        latest[0] = earliest[0] = -1;  // Pretty critical here! To make sure we get 0th index.
        for (int i=0; i<nums.size(); i++) {
            sum += nums[i];
            if (earliest.find(sum) == earliest.end()) {earliest[sum] = i;}
            latest[sum] = i;
        }
        
        int max_len=0;
        for (const auto& kv : latest) {
            int val = kv.first;
            int search = val-k;
            if (earliest.find(search) != earliest.end()) {
                int my_len = kv.second - earliest[search];
                max_len = std::max(my_len, max_len);
            }
        }
        return max_len;
    }
};
