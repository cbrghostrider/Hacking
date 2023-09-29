// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//same idea as 046_permutations, but keep track of which numbers were chosen
//and don't recurse on duplicates!
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if (nums.size() == 0) {
            vector<int> inner;
            vector<vector<int> > outer;
            outer.push_back(inner);
            return outer;
        }
        
        vector<vector<int> > retval;
        unordered_set<int> chosenNums; //don't choose duplicates to recurse on
        for (unsigned int i=0; i<nums.size(); i++) {
            vector<int> recurse = nums;
            if (chosenNums.find(recurse[i]) != chosenNums.end()) continue; 
            
            std::swap(recurse[i], recurse[recurse.size() - 1]);
            int chosen = recurse.back();
            recurse.pop_back();
            chosenNums.insert(chosen);
            
            vector<vector<int> > perms = permuteUnique(recurse);
            for_each(perms.begin(), perms.end(), [chosen] (vector<int>& vec) -> void {
                vec.push_back(chosen);
            });
            
            retval.insert(retval.end(), perms.begin(), perms.end());
        }
        
        return retval;
    }
};
