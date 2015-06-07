// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//note, C++ has a std::next_permutation() to do this exact thing
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() < 2) return; 
        
        //find monotonically non-decreasing sequence from the back
        int ind=0;
        for (ind=nums.size()-2; ind>=0; ind--) {
            if (nums[ind] < nums[ind+1]) break;
        }
        
        //reverse it
        std::reverse(nums.begin() + ind + 1, nums.end());
        if (ind == -1) return;   //entire array was reverse sorted
        
        //find element in that sequence that is bigger than the element just before the sequence
        int chosen = nums[ind];
        auto fit = find_if(nums.begin() + ind + 1, nums.end(), [chosen] (const int& num) -> bool {return (num > chosen);});
        
        //and swap them!
        std::swap(nums[ind], *fit);
    }
};
