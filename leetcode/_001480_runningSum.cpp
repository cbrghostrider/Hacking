class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> rsum;
        int sum = 0;
        for (int n : nums) {
            sum += n;
            rsum.push_back(sum);
        }
        return rsum;
    }
};
