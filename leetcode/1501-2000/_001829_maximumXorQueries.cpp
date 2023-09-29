class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        uint32_t xval=0;
        for (int n : nums) {xval ^= (uint32_t)n;}
        
        const uint32_t kmask = (1<<maximumBit);
        
        vector<int> ans;
        for (int i=0; i<nums.size(); i++) {
            // xval is currently the partial xor, for entire array but not chosen k
            
            uint32_t mask = kmask >> 1;
            
            uint32_t val=0;
            while (mask != 0) {
                if ((mask & xval) == 0) {
                    val |= mask;
                }
                mask >>= 1;
            }
            ans.push_back(val);
            
            xval ^= nums[nums.size()-1-i];
        }
        
        return ans;
    }
};
