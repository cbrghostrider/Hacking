class Solution {
public:
    // O(n) time, O(1) space.
    bool check(vector<int>& nums) {
        if (nums.size() == 1) return true;
        int allowed = 1;
        for (int i=1; i<nums.size(); i++) {
            if (nums[i-1] > nums[i]) {
                if (allowed) allowed--;
                else return false;
            }
        }
        // compare wraparound
        if (nums[nums.size()-1] > nums[0]) {
            return allowed;
        }
        return true;
    }
};
