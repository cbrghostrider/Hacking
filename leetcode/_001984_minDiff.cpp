class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        int min_diff = std::numeric_limits<int>::max();
        for (int i=k-1; i<nums.size(); i++) {
            int diff = nums[i] - nums[i-(k-1)];
            if (diff < min_diff) min_diff = diff;
        }
        return min_diff;
    }
};
