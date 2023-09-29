class Solution {
public:        
    // O(n) time, O(n) space.
    int maxSumAfterOperation(vector<int>& nums) {
        const int N=nums.size();
        // dp[i][0] is the max subarray sum including nums[i] and without squaring any element.
        // dp[i][1] is the max subarray sum including nums[i] and having only one element squared.
        vector<vector<int>> dp(N, vector<int>(2, 0));
        
        // Base case.
        dp[0][0] = nums[0];
        dp[0][1] = nums[0]*nums[0];
        int running_sum = nums[0];
        int max_choice = dp[0][1];
        
        for (int i=1; i<N; i++) {
            int my_running_sum = running_sum + nums[i];
            dp[i][0] = running_sum = (my_running_sum > nums[i] ? my_running_sum : nums[i]);
            
            // for dp[i][1] we have 3 choices
            // either square element i, and look up dp[i-1][0]
            // or don't square element i, and look up dp[i-1][1]
            // or just current number squared
            int choice1 = nums[i]*nums[i] + dp[i-1][0];
            int choice2 = nums[i] + dp[i-1][1];
            int choice3 = nums[i] * nums[i];
            dp[i][1] = std::max(std::max(choice1, choice2), choice3);
            if (dp[i][1] > max_choice) {
                max_choice = dp[i][1];
            }
        }
        return max_choice;
    }
};
