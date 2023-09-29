// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        const int N = costs.size();
        const int C = 3; //3 colors
        
        //let mc(i, j) denote the minimum cost of painting the first i houses, such that
        //the last house (ith house) was painted color j
        vector<int> prevMC(3, 0);
        vector<int> nextMC(3, 0);
        
        //base case, cost for painting first 1 houses, with house 0 in desired color
        prevMC[0] = costs[0][0];
        prevMC[1] = costs[0][1];
        prevMC[2] = costs[0][2];
        
        for (int h=1; h<costs.size(); h++) {
            nextMC[0] = std::min(prevMC[1] + costs[h][0], prevMC[2] + costs[h][0]);
            nextMC[1] = std::min(prevMC[0] + costs[h][1], prevMC[2] + costs[h][1]);
            nextMC[2] = std::min(prevMC[0] + costs[h][2], prevMC[1] + costs[h][2]);
            prevMC = nextMC;
        }
        
        return (std::min(prevMC[0], std::min(prevMC[1], prevMC[2])));
    }
};
