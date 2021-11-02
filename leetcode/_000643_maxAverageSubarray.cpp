class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double rolling_sum = 0;
        
        int i = 0;
        for (; i<k; i++) { rolling_sum += nums[i]; }
        
        double max_sum = rolling_sum;
        for (int j=0; i<nums.size(); i++, j++) {
            rolling_sum += nums[i] - nums[j];
            if (rolling_sum > max_sum) {
                max_sum = rolling_sum;
            }
        }
        
        return max_sum / k;
    }
};
