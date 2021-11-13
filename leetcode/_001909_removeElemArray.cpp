class Solution {
public:
    // O(n) time, O(1) space.
    bool canBeIncreasing(vector<int>& nums) {
        if (nums.size() <= 2) return true;

        int strikes = 1;
        int last = nums[0];
        
        for (int i=1; i<nums.size(); i++) {
            if (nums[i] <= last) {
                if (strikes == 1) {
                    strikes--;  //throw out one element
                    bool nums_i_works = 
                        (i == 1 || nums[i-2] < nums[i]) && 
                        (i == nums.size()-1 || nums[i] < nums[i+1]);
                    bool nums_i_m_1_works = 
                        (i == 1 || nums[i-2] < nums[i-1]) && 
                        (i == nums.size()-1 || nums[i-1] < nums[i+1]);
                    if (!nums_i_works && !nums_i_m_1_works) return false;
                    if (nums_i_works) last = nums[i];        // throw out nums[i-1]
                    if (nums_i_m_1_works) last = nums[i-1];  // throw out nums[i]
                } else {
                    return false;
                }
            } else {
                last = nums[i];
            }
        }
        return true;
    }
};
