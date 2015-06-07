// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        unordered_map<int, int> nums;
        vector<vector<int> > waysToTgt[target+1]; //find out all ways a target can sum to this value
        vector<vector<int> > accum;
        
        for (const int& cand : candidates) {
            auto it = nums.find(cand);
            if (it == nums.end()) {
                nums.insert(make_pair(cand, 1));    
            } else {
                it->second += 1;
            }
        }
        
        //cannot have 0 as one of the candidate numbers, because then you have infinite ways to sum to tgt
        if (candidates.size() == 0 || (nums.find(0) != nums.end())) return vector<vector<int>>();
        
        //base case target is 1: 1 way to do this if possible
        if (nums.find(1) != nums.end()) {
            vector<int> result; result.push_back(1);
            accum.push_back(result);
        }

        waysToTgt[1] = accum;
        accum.clear();
        
        //dynamic programming loop
        for (int tgt = 2; tgt <= target; tgt++) {
            int limit = (tgt / 2);
            for (int choice = 1; choice <= limit; choice++) {
                int otherChoice = tgt - choice;
                vector<vector<int>> waysToChoice = waysToTgt[choice];
                vector<vector<int>> waysToOtherChoice = waysToTgt[otherChoice];
                for (vector<int>& c1 : waysToChoice) {
                    for (vector<int>& c2 : waysToOtherChoice) {
                        bool flag = false;
                        vector<int> result = c1;
                        result.insert(result.end(), c2.begin(), c2.end());
                        sort(result.begin(), result.end());
                        
                        //throw out results that use too many candidates of the same number
                        vector<int> cnt((choice > otherChoice ? choice : otherChoice) + 1, 0);
                        for (int & check : result) cnt[check] += 1;
                        for (int i=1; i<cnt.size(); i++) {
                            auto it = nums.find(i);
                            if (it == nums.end()) continue; 
                            if (cnt[i] > it->second) flag = true;
                        }
                        if (flag) continue;
                        
                        accum.push_back(result);
                    }
                }
            }
            if (nums.find(tgt) != nums.end()) {
                vector<int> numLoner; numLoner.push_back(tgt);   
                accum.push_back(numLoner);
            }
            sort(accum.begin(), accum.end());
            auto uit = unique(accum.begin(), accum.end());
            accum.erase(uit, accum.end());
            waysToTgt[tgt] = accum;
            accum.clear();
        }
        return waysToTgt[target];
    }
};

