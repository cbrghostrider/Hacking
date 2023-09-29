// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        if (n < k || n < 0 || k < 0) return vector<vector<int>>(); //undefined problem
        
        //dynamic programming cache
        vector<vector<int>> cache[n+1][n+1];
        
        vector<vector<int>> setOfEmptySet(1, vector<int>());
        //base cases
        for (int ni=0; ni<=n; ni++) {
            for (int ki=0; ki<=n; ki++) {
                if (ni < ki) cache[ni][ki] = vector<vector<int>>(); //undefined problem
                else if (ki == 0) cache[ni][ki] = setOfEmptySet;    //[]
            }
        }
        
        //dynamic programming loop
        for (int ni=1; ni<=n; ni++) {
            for (int ki=1; ki<=k; ki++) { //note; limit to ki<=k instead of ki<=ni because
                                          //we are only interested in nCk (and not beyond k)
                int chosen = ni;
                vector<vector<int>> recordDrop = cache[ni-1][ki];  //drop this number
                vector<vector<int>> recordTake = cache[ni-1][ki-1];//take this number
                for (vector<int>& rec : recordTake) {
                    rec.push_back(chosen);
                }
                recordDrop.insert(recordDrop.end(), recordTake.begin(), recordTake.end());
                cache[ni][ki] = recordDrop;
            }
        }
        return cache[n][k];
    }
};
