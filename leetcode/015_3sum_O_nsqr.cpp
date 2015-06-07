// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    unordered_map<int, int> bag;
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > soln;

        for (int i=0; i<nums.size(); i++) {
            auto it=bag.find(nums[i]);
            bag[nums[i]] = (it == bag.end()) ? 1 : (1 + bag[nums[i]]) ;
        }
        
        //this only processes the single special case where we have 3 zeros
        if (bag.find(0) !=bag.end() && bag[0] >= 3) {
            soln.push_back(vector<int>(3, 0)); //[0, 0, 0] is a solution
        }

        //this processes the special cases where we have 2 or more duplicates
        for (pair<const int, int>& bv : bag) {
            if (bv.second <= 1) continue; 
            if (bv.first == 0) continue;   //not considering 0 again
            auto it = bag.find((-1) * bv.first * 2); 
            if (it == bag.end()) continue;
            vector<int> triple = {bv.first, bv.first, it->first};
            sort(triple.begin(), triple.end());
            soln.push_back(triple);
        }
        
        //now get rid of all those pesky duplicates
        sort(nums.begin(), nums.end());
        nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
        
        //and find what we need from sorted unique sequence
        for (int i=0; i < nums.size() ; i++) {
            for (int j=i+1; j < nums.size(); j++) {
                int check = (-1)*(nums[i] + nums[j]);
                auto it = bag.find(check);
                if (it == bag.end()) continue; //number not found
                if (check <= nums[j]) continue;//so that we don't get duplicate results 
                vector<int> triplet = {nums[i], nums[j], check};
                soln.push_back(triplet);
            }
        }        
        return soln;
    }
};

