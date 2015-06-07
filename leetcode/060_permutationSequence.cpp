// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//picks each number 1 by 1
//the basic logic is as follows:
//say you have n = 9 and k = 300000. i.e. we want the 300000th sequence for 9!
//if I fix the first digit to 1, I have 8! permutations to choose from (2..9)
//if I fix the first digit to 2, I have 8! permutations to choose from (1, 3..9) and so on
//i.e. each time I fix a MSB to a digit, I eat up 40320 (factorial 8) combinations
//therefore by dividing by factorial[9-1] (dmsb = k / factorial[nc-1]) and 
//choosing the dmsb-th smallest remaining number I can correct choose this digit
//
//then just continue the process down the line to get the answer
class Solution {
    int factorial[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
    
public:
    string getPermutation_(vector<int>& nums, int k) {
        string thisDig, rest;
        if (nums.size() == 0) return "";
        
        int nc = nums.size();
        if (((k / factorial[nc-1]) == 0) ){
            thisDig = std::to_string(nums[0]); //pick the minimum
            nums.erase(nums.begin());
            rest = getPermutation_(nums, k);
        } else {
            int myInd = (k / factorial[nc-1]);
            thisDig = std::to_string(nums[myInd]);
            nums.erase(nums.begin() + myInd);
            rest = getPermutation_(nums, (k % factorial[nc-1]));
        }
        return (thisDig + rest);
    }
    
    string getPermutation(int n, int k) {
        if (k > factorial[n]) return "";
        vector<int> nums;
        for (int i=1; i<=n; i++) nums.push_back(i);
        return (getPermutation_(nums, k-1));
    }
};
