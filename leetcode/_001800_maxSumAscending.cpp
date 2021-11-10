class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int max_sum = nums[0];
        int sum = nums[0];
        for (int i=1; i<nums.size(); i++) {
            if (nums[i-1] < nums[i]) {
                sum += nums[i];
            } else {
                if (max_sum < sum) max_sum = sum;
                sum = nums[i];
            }
        }
        return std::max(max_sum, sum);
    }
};
