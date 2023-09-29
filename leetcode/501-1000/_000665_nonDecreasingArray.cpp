// Check for first violation (say between i and i+1 indices)
// Choices are:
// 1. Either make i == element at index (i-1) [Or MIN if i==0] and keep checking
// 2. Or make i+1 == element at index i (Or MAX if i == N-1) and keep checking
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        if (nums.size() <= 2) return true;
        
        bool strike=true;
        for (int i=0; i<nums.size()-1; i++) {
            if (nums[i] <= nums[i+1]) { continue; }
            if (strike == false) return false;
            if (i == nums.size()-2) {
                if (strike == false) return false;
                else continue;  // last pair has inequality, we are OK.
            }
            
            // Option 1: treat nums[i] as nums[i-1] (Or MIN)
            if (i == 0 || nums[i-1] <= nums[i+1]) {
                nums[i] = i == 0? -10000 : nums[i-1];
                strike = false;  // used up one strike
            } else {  // Option 2
                nums[i+1] = nums[i];
                strike = false;
            }
        }
        return true;
    }
};
