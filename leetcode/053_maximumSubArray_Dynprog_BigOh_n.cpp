class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        
        //dynamic programming cache- Ci: Stores sum of max subarr from i down to some index k
        int maxSubArr[nums.size()];
        maxSubArr[0] = nums[0];
        int maxval = nums[0];
        
        //dyn programming loop (compute Ci)
        for (int ind = 1; ind < nums.size(); ind++) {
            int cand1 = maxSubArr[ind-1] + nums[ind];
            int cand2 = nums[ind];
            maxSubArr[ind] = cand1 > cand2 ? cand1 : cand2;
            if (maxSubArr[ind] > maxval) maxval = maxSubArr[ind];
        }
        return maxval;
    }
};
