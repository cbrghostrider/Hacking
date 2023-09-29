class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int sum = 0;
        for (int i=0, j=1; j<nums.size(); i+=2, j+=2) {
            sum += min(nums[i], nums[j]);
        }
        return sum;
    }
};
