class Solution {
public:
    // O(n log n) time, O(1) space (other than ans).
    vector<int> targetIndices(vector<int>& nums, int target) {
        vector<int> ans;
        std::sort(nums.begin(), nums.end());
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] == target) {ans.push_back(i);}
        }
        return ans;
    }
};
