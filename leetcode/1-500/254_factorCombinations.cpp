// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    vector<vector<int>> getFactors_(int n) {
        if (n == 0 || n == 1) return vector<vector<int>>(); 
        
        int upto = ceil(sqrt((double)n));
        vector<vector<int>> retval;
        for (int fact1=2; fact1<=upto; fact1++) {
            if ((n%fact1) == 0) {
                vector<vector<int>> combos = getFactors_(n/fact1);
                for (vector<int>& c : combos) {
                    c.push_back(fact1);
                    std::sort(c.begin(), c.end());
                    retval.push_back(c);
                }
            }
        }
        retval.push_back(vector<int>(1, n));
        std::sort(retval.begin(), retval.end(), [] (const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs.size() != rhs.size()) return (lhs.size() < rhs.size());
            for (int i=0; i<lhs.size(); i++) {
                if (lhs[i] != rhs[i]) return (lhs[i] < rhs[i]);
            }
            return false; //both equal should always return false
        });
        auto it = std::unique(retval.begin(), retval.end(), [] (const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs.size() != rhs.size()) return false;
            for (int i=0; i<lhs.size(); i++) {
                if (lhs[i] != rhs[i]) return false;
            }    
            return true;
        });
        retval.erase(it, retval.end());
        return retval;
    }
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> ans = getFactors_(n);
        vector<int> removeMe(1, n);
        auto it = std::find(ans.begin(), ans.end(), removeMe);
        if (it != ans.end()) ans.erase(it);
        return ans;
    }
};
