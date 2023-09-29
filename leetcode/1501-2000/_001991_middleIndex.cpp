class Solution {
public:
    int findMiddleIndex(vector<int>& nums) {
        int total = 0;
        for (int n : nums) total += n;
        
        int sum = 0;
        for (int i=0; i<nums.size(); i++) {
            if (sum == (total - nums[i] - sum)) return i;
            sum += nums[i];
        }
        return -1;
    }
};
