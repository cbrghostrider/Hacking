// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    
    //give me all combination of k numbers that adds to addsTo, 
    //using numbers between [(greaterthan + 1)..9] only once
    vector<vector<int>> comboSum(int k, int addsTo, int greaterThan) {
        if (k == 0 && addsTo == 0) { //done
            return vector<vector<int>>(1, vector<int>()); 
        }
        if (k == 0 || addsTo <= greaterThan) { //not possible
            return vector<vector<int>>();  
        }
        vector<vector<int>> retval;
        for (int n=greaterThan+1; n<10; n++) {
            int recAddsTo = addsTo - n;
            if (recAddsTo < 0) continue;
            
            vector<vector<int>> reccombos = comboSum(k-1, recAddsTo, n);
            
            for (vector<int>& rcombo : reccombos) {
                rcombo.push_back(n);
                retval.push_back(rcombo);
            }
        }
        return retval;
    }
    
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        if (n > 45 || k <= 0) return vector<vector<int>>();
        vector<vector<int>> ans = comboSum(k, n, 0);
        for (vector<int>& vi : ans) {
            std::sort(vi.begin(), vi.end());
        }
        return ans;
    }
};
