class Solution {
    // Dynamic Programming;
    // let dp(i) denote the answer considering nums up to index i
    // there are two parts to dp(i)
    // 1. We can ignore the ith element, and take all the triangles that we got up to i-1 th element
    //       this is dp(i-1)
    // 2. We can consider i-th element, and see which previous 2 sides participate in valid triangles.
    //       Basically any 2 prev sides that sum to >= the new length is a valid triangle
    //       We count this in ge_me component of the sum.
    // 
    // Finally we have to update the sum_counts for the contribution made with the new element.
public:    
    // O(n^2) time, O(n^2) space.
    int triangleNumber(vector<int>& nums) {
        if (nums.size() <= 2) return 0;
        std::sort(nums.begin(), nums.end());
        
        // stores the sum of 2 sides for all lengths seen so far.
        map<int, int> sum_counts;
        
        // stores the dp computation; only need the last one really
        vector<int> dp(nums.size(), 0);
        
        // Base cases.
        dp[0] = dp[1] = 0;
        sum_counts[nums[0] + nums[1]] = 1;
        
        for (int i=2; i<nums.size(); i++) {
            int ge_me=0;
            for (auto it=sum_counts.rbegin(); it != sum_counts.rend(); it++) {
                if (it->first <= nums[i]) break;
                ge_me += it->second;
            }
            dp[i] = dp[i-1] + ge_me;
            
            // update sum_counts
            for (int j=0; j<i; j++) {
                int my_sum = nums[i] + nums[j];
                sum_counts[my_sum]++;
            }
        }
        return dp[nums.size()-1];
    }
};
