class Solution {
public:
    // DP: O(n^2) time, O(n) space.
    // Functionally correct, but...
    // This solution gets TLE For larger sized n.
    int shortestSubarray(vector<int>& nums, int k) {
        // sums[i][sz] stores sum of subarray starting at i, of size sz.
        vector<vector<int>> sums(nums.size(), vector<int>(nums.size()+1, 0));
        
        // Base case.
        for (int i=0; i<nums.size(); i++) {
            sums[i][1] = nums[i];
            if (sums[i][1] >= k) return 1;
        }
        
        // DP.
        for (int sz=2; sz<=nums.size(); sz++) {
            for (int i=nums.size()-sz; i>=0; i--) {
                sums[i][sz] = sums[i+1][sz-1] + nums[i];
                if (sums[i][sz] >= k) return sz;
            }
        }
        return -1;
    }
};
