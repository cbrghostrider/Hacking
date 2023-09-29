class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        const int N = nums.size();
        vector<int> ans(nums.size()*2, 0);
        for (int i=0; i<N; i++) {
            ans[i] = nums[i];
            ans[i+N] = nums[i];
        }
        return ans;
    }
};
