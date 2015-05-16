// similar to std::unique()
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size(); 
        int check=1, copy=0;
        for (; check < nums.size(); check++) {
            if (nums[check] == nums[copy]) continue;
            nums[++copy] = nums[check];
        }
        return (copy+1);
    }
};
