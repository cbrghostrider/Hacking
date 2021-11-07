class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans;
        const int limit = nums.size()/2;
        for (int i=0; i<limit; i++) {
            ans.push_back(nums[i]);
            ans.push_back(nums[limit + i]);
        }
        return ans;
    }
};
