// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    vector<vector<int>> subsetsWithDup_(vector<int>& nums) {
        vector<vector<int>> retval;
        if (nums.empty()) {
            retval.push_back(vector<int>());
            return retval;
        }
        
        int chosen = nums.back(); nums.pop_back();
        vector<vector<int>> recurse = subsetsWithDup_(nums);
        for (vector<int>& ss : recurse) {
            bool shouldDrop = (std::find(ss.begin(), ss.end(), chosen) == ss.end());
            if (shouldDrop) retval.push_back(ss); //drop chosen
            ss.push_back(chosen);
            retval.push_back(ss);                 //take chosen
        }
        return retval;
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return (subsetsWithDup_(nums));
    }
};
