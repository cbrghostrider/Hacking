class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max1 = std::max(nums[0] - 1, nums[1] - 1);
        int max2 = std::min(nums[0] - 1, nums[1] - 1);
        int min1 = max2;
        int min2 = max1;
        for (int i=2; i<nums.size(); i++) {
            int n = nums[i];
            if (n-1 >= max1) {
                max2 = max1; 
                max1 = n-1;
            } else if (n-1 > max2) {
                max2 = n-1;
            }
            if (n-1 <= min1) {
                min2 = min1; 
                min1 = n-1;
            } else if (n-1 < min2) {
                min2 = n-1;
            }
        }
        return std::max(max1 * max2, min1 * min2);
    }
};
