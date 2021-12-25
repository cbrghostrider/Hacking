class Solution {
    vector<int> csum;
    
    string signature(int index, int target) {
        return (to_string(index) + ":" + to_string(target));
    }
    unordered_map<string, int> cache;
    
    int ways(vector<int> nums, int index, int target) {
        string sig = signature(index, target);
        if (cache.find(sig) != cache.end()) return cache[sig];
                if (nums.size() == 0 || index < 0){
            cache[sig] = target == 0 ? 1 : 0;
            return cache[sig];
        }
        if (target > csum[index] || target < -1*csum[index]) {
            cache[sig] = 0;
            return 0;
        }
        
        int elem= nums.back();
        nums.pop_back();
        
        // Add it; so recursed has to sub to keep on target.
        int ways_add = ways(nums, index-1, target-elem);
        
        // Sub it; so recursed has to add it back to keep on target.
        int ways_sub = ways(nums, index-1, target+elem);
        
        cache[sig] = ways_add + ways_sub;
        return cache[sig];
    }
    
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=0;
        for (int n : nums) {sum += n; csum.push_back(sum);}
        
        int ways_ret = ways(nums, nums.size()-1, target);
        return ways_ret;        
    }
};
