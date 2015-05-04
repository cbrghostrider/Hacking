class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        for (unsigned int i=0; i<nums.size(); i++) {
            bool evalPrev = (i == 0)                 || (nums[i] > nums[i-1]);
            bool evalNext = (i == (nums.size() - 1)) || (nums[i] > nums[i+1]);
            if (evalPrev && evalNext) return i;
        }
        return -1; //not defined or found
    }
};
