class Solution {
    const uint32_t mask = 0xc0000000;
    
    int getRawNum(int num) {
        return ((uint32_t)num) & ~mask;
    }
    
    int getCounter(int num) {
        return (((uint32_t)num) & mask) >> 30;
    }
        
    void incCounter(vector<int>& nums, int index) {
        uint32_t ctr = getCounter(nums[index]);
        ctr++;
        nums[index] = getRawNum(nums[index]);
        nums[index] |= (ctr << 30);
    }
public:
    // O(n) time, constant space.
    vector<int> findDuplicates(vector<int>& nums) {
        
        for (int i=0; i<nums.size(); i++) {
            int raw_num = getRawNum(nums[i]);
            incCounter(nums, raw_num-1);
        }
        vector<int> ans;
        for (int i=0; i<nums.size(); i++) {
            int ctr = getCounter(nums[i]);
            if (ctr > 1) ans.push_back(i+1);
        }
        return ans;
    }
};
