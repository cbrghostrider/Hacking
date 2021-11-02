class Solution {
    struct Data {
        int left_sum = 0;
        int right_sum = 0;
    };
    std::vector<Data> sums;
public:
    // O(n) space, O(n) time
    int pivotIndex2(vector<int>& nums) {
        sums = vector<Data>(nums.size(), {0, 0});
        int sum = 0;
        for (int i=0; i<nums.size(); i++) {
            sums[i].left_sum = sum;
            sum += nums[i];
        }
        sum = 0;
        for (int i=nums.size()-1; i>=0; i--) {
            sums[i].right_sum = sum;
            sum += nums[i];
        }
        for (int i=0;i<sums.size(); i++) {
            if (sums[i].left_sum == sums[i].right_sum) return i;
        }
        return -1;
    }
    
    // O(1) space, O(n) time
    int pivotIndex(vector<int>& nums) {
        if (nums.size() == 0) return -1;
        if (nums.size() == 1) return 0;
        
        int right_sum = 0;
        std::for_each(nums.begin(), nums.end(), [&right_sum](int num) {right_sum += num;});
        
        int left_sum = 0;
        for (int i=0; i<nums.size(); i++) {
            right_sum -= nums[i];
            if (left_sum == right_sum) return i;
            left_sum += nums[i];
        }
        return -1;
    }
};
