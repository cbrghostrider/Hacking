class Solution {
public:
    // O(n) time, O(1n) space
    vector<int> sortedSquares(vector<int>& nums) {
        // Note special case: everything is negative.
        const bool all_negs = nums[nums.size()-1] < 0;
        if (all_negs) {
            for (int i=0; i<nums.size()/2; i++) {
                int j = nums.size()-1-i;
                int temp = nums[j];
                nums[j] = nums[i] * nums[i];
                nums[i] = temp * temp;
            }
            if (nums.size()%2) {
                int mid = nums.size()/2;
                nums[mid] = nums[mid] * nums[mid];
            }
            return nums;
        }
        
        int first_pos = -1, last_neg = -1;  // indices
        for (int i=0; i<nums.size(); i++) {
            if (first_pos == -1 && nums[i]>=0) {
                first_pos = i;
                last_neg = i-1;
            }
            nums[i] = nums[i] * nums[i];
        }
        
        if (first_pos == -1) return nums;
        
        // merge two sorted sequences
        vector<int> ns(nums.size(), 0);
        int i=0;
        for (; i<ns.size() && first_pos<ns.size() && last_neg >=0; i++) {
            if (nums[first_pos] < nums[last_neg]) {
                ns[i] = nums[first_pos++];
            } else {
                ns[i] = nums[last_neg--];
            }
        }
        while (last_neg >= 0) {
            ns[i++] = nums[last_neg--];
        }
        while (first_pos < nums.size()) {
            ns[i++] = nums[first_pos++];
        }
        return ns;
    }
};
