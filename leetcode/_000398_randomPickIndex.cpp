class Solution {
    unordered_map<int, vector<int>> nums_to_indices;
public:
    Solution(vector<int>& nums) {
        for (int i=0; i<nums.size(); i++) {
            nums_to_indices[nums[i]].push_back(i);
        }
    }
    
    int pick(int target) {
        if (nums_to_indices.find(target) == nums_to_indices.end()) return -1;
        int sz = nums_to_indices[target].size();
        int r = std::rand() % sz;
        return nums_to_indices[target][r];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
