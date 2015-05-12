class Solution {

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        unordered_set<int> nums;
        vector<vector<int> > waysToTgt[target+1]; //find out all ways a target can sum to this value
        vector<vector<int> > accum;
        
        for (const int& cand : candidates) nums.insert(cand);
        
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
                        vector<int> result = c1;
                        result.insert(result.end(), c2.begin(), c2.end());
                        sort(result.begin(), result.end());
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
