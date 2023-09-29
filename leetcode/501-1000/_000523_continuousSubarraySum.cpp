class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {        
        // (csum is key, earliest such index is value)
        unordered_map<long, int> csums;
        long sum=0;
        csums[0] = -1;        
        
        for (int i=0; i<nums.size(); i++) {
            sum += nums[i];
                        
            for (long mult=sum/k; mult >=0; mult--) {
                long check = sum - mult*k;
                if (csums.find(check) != csums.end()) {                    
                    if (i-csums[check] >= 2) return true;                    
                }                
            }
            
            if (csums.find(sum) == csums.end()) { csums[sum] = i; }
        }
        return false;
    }
};
