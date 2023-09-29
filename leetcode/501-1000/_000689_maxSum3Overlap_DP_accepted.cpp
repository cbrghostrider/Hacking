class Solution {
    struct Info {
        // The starts of subarrays of length k.
        vector<int> starts;
        // The sum of all subarrays above.
        int sum=0;
    };
    
    vector<int> nums;
    
    // contains the sum of subarrays of len k starting at index
    // {[0..k-1], [1..k], [2...k+1], ...}
    vector<int> ksums;

public:
    // O(n) time, O(n) space.
    vector<int> maxSumOfThreeSubarrays(vector<int>& n, int k) {
        if (n.size() < k*3) return {};
        nums = n;
        
        // Initialization
        int sum=0;
        for (int i=0; i<k; i++) {
            sum += nums[i];
        }
        ksums.push_back(sum);
        
        for (int i=k; i<nums.size(); i++) {
            sum -= nums[i-k];
            sum += nums[i];
            ksums.push_back(sum);
        }
        
        vector<vector<Info>> dp(nums.size(), vector<Info>(4, Info()));
        
        // base case; rem==1
        for (int i=nums.size()-k; i>=0; i--) {
            Info my_info = {{i}, ksums[i]};
            if (i+1 < nums.size() && my_info.sum < dp[i+1][1].sum) {
                my_info = dp[i+1][1];
            }
            dp[i][1] = my_info;
        }
        
        for (int rem=2; rem<=3; rem++) {            
            for (int i=nums.size()-k*rem; i>=0; i--) {
                // I don't pick subarray of size k at i
                Info cand_down = i+1 < nums.size() ? dp[i+1][rem] : Info();
                
                // I pick subarray of size k at i
                Info my_info;
                int my_sum = ksums[i];
                if (i+k < nums.size() && dp[i+k][rem-1].starts.size() == rem-1) {
                    const Info& down = dp[i+k][rem-1];
                    my_info = {{i}, my_sum};
                    my_info.starts.insert(my_info.starts.end(), down.starts.begin(), down.starts.end());
                    my_info.sum += down.sum;
                }
                if (cand_down.sum > my_info.sum) {
                    dp[i][rem] = cand_down;
                } else {
                    dp[i][rem] = my_info;
                }
            }
        }
        
        return dp[0][3].starts;
    }    
};
