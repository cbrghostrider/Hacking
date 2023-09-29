class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.size() == 0 || nums.size() == 1) return nums.size();
        
        int longest = 1;
        int curr_start = 0;
        for (int ptr = 1; ptr < nums.size(); ptr++) {
            if (nums[ptr] > nums[ptr-1]) continue;
            int curr_length = ptr - curr_start;
            if (curr_length > longest) {
                longest = curr_length;
            }
            curr_start = ptr;
        }
        int end_length = nums.size() - curr_start;
        return (end_length > longest ? end_length : longest);
    }
};
