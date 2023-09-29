// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(n) time and O(1) space
//
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int prefixProd = 1;
        int suffixProd = 1;
        
        vector<int> output(nums.size(), 1);
        for (int i=0; i<nums.size(); i++) {
            if (i != 0) prefixProd *= nums[i-1];
            output[i] *= prefixProd;
        }
        for (int i=nums.size()-1; i>=0; i--) {
            if (i != nums.size()-1) suffixProd *= nums[i+1]; 
            output[i] *= suffixProd;
        }
        return output;
    }
};
