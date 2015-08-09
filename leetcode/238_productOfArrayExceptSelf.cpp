// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(n) space and O(n) time
//
class Solution {
    vector<int> prefixProd;
    vector<int> suffixProd;
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        prefixProd = vector<int>(nums.size(), 1);
        suffixProd = vector<int>(nums.size(), 1);
        
        for (int i=1; i<nums.size(); i++) {
            prefixProd[i] = prefixProd[i-1] * nums[i-1];
        }
        
        for (int i=nums.size()-2; i>=0; i--) {
            suffixProd[i] = suffixProd[i+1] * nums[i+1];
        }
        
        vector<int> output(nums.size(), 0);
        for (int i=0; i<nums.size(); i++) {
            output[i] = prefixProd[i] * suffixProd[i];
        }
        return output;
    }
};
