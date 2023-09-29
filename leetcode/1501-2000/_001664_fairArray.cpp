class Solution {
public:
    // O(n) forward and backward scans.
    int waysToMakeFair(vector<int>& nums) {
        // The sum of alternate indices from the LHS; value of index i included in the sum.
        vector<int> lhs_sum(nums.size(), 0);
        // The sum of alternate indices from the RHS; value of index i included in the sum.
        vector<int> rhs_sum(nums.size(), 0);
        
        int even_sum=0, odd_sum=0;
        for (int i=0; i<nums.size(); i++) {
            if (i % 2 == 0) {even_sum += nums[i]; lhs_sum[i] = even_sum; }
            else {odd_sum += nums[i]; lhs_sum[i] = odd_sum; }
        }
        even_sum=0, odd_sum=0;
        for (int i=nums.size()-1; i>=0; i--) {
            if (i % 2 == 0) {even_sum += nums[i]; rhs_sum[i] = even_sum; }
            else {odd_sum += nums[i]; rhs_sum[i] = odd_sum; }
        }
        
        int total=0;
        // Simulate removal of each element.
        for (int i=0; i<nums.size(); i++) {
            int lhs_sum_prev = (i == 0 ? 0 : lhs_sum[i-1]);
            int lhs_sum_prev_prev = (i <= 1 ? 0 : lhs_sum[i-2]);
            int rhs_sum_next = (i == ((int)nums.size())-1 ? 0 : rhs_sum[i+1]);
            int rhs_sum_next_next = (i >= ((int)nums.size())-2 ? 0 : rhs_sum[i+2]);
            if (lhs_sum_prev_prev + rhs_sum_next == lhs_sum_prev + rhs_sum_next_next) {
                total++;
            }
        }
        return total;
    }
};
