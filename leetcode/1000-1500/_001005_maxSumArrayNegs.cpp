class Solution {
public:
    // O(nlogn) time, O(1) space.
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        bool has_zero = false;
        for (int n : nums) {if (n == 0) has_zero = true;}
        
        std::sort(nums.begin(), nums.end());
        for (int i=0; i<nums.size() && k > 0; i++) {
            int& n = nums[i];
            if (n < 0) {
                n = -1 * n;
                k--;
            } else {
                break;
            }
        }
        
        if (has_zero) {k = 0;}
        std::sort(nums.begin(), nums.end());
        if (k % 2) {
            nums[0] = nums[0] * -1;
        }
        int ans = 0;
        std::for_each(nums.begin(), nums.end(), [&ans](int n) {
            ans += n;
        });
        return ans;
    }
};
