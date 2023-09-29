class Solution {
    int scan_right = 0;
public:
    void swap_with_even(vector<int>& nums, int index) {
        while (scan_right >= 0 && 
               ! ((scan_right%2 != 0) && nums[scan_right]%2 == 0)) {
            // Found last odd index even number from the right.
            scan_right--;
        }
        if (scan_right >= 0) {
            int temp = nums[index];
            nums[index] = nums[scan_right];
            nums[scan_right] = temp;
        }
    }
    
    // O(n) time and O(1) space.
    vector<int> sortArrayByParityII(vector<int>& ns) {
        vector<int> nums = ns;
        scan_right = nums.size()-1;
        
        for (int i = 0; i<nums.size(); i++) {
            if ((i%2 == 0) && (nums[i]%2 != 0)) {
                swap_with_even(nums, i);
            }
        }
        return nums;
    }
};
