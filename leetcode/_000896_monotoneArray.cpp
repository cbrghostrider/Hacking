class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        bool monotone_inc = true, monotone_dec = true;
        int last = std::numeric_limits<int>::min();
        for (int i=0; i<nums.size(); i++) {
            if (!(last <= nums[i])) {
                monotone_inc = false;
                break;
            }
            last = nums[i];
        }
        last = std::numeric_limits<int>::min();
        for (int i=nums.size()-1; i>=0; i--) {
            if (!(last <= nums[i])) {
                monotone_dec = false;
                break;
            }
            last = nums[i];
        }
        return (monotone_inc || monotone_dec);
    }
};
