// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(n k log k), can easily extend to O(n k)
//
// This is an extension of the problem with only 3 colors. Consider color c' as the mincost color 
// for the prev subproblem. i.e. c' is the color of the last house for the prev subproblem, such that 
// cost is minimum. For current house, all colors except c' can use this mincost subproblem.
// For painting current house c', we need the *second* mincost from previous subproblem.
//
// I used a minheap to store the previous mincosts, and just pop it once. In fact, you can extend 
// this solution and scan linear through the prev costs to remember the minimum and second minimum cost. 
// This will get rid of the log k factor in my solution I believe.
//
struct ColorInfo {
    int color, cost;
    ColorInfo(int cl, int cst) : color(cl), cost(cst) {}
};

struct ColorCmpLess {
    bool operator() (const ColorInfo& lhs, const ColorInfo& rhs) { return (lhs.cost > rhs.cost); }  
};

class Solution {
    typedef priority_queue<ColorInfo, vector<ColorInfo>, ColorCmpLess> MinColorHeap;
public:
    int minCostII(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        const int N = costs.size();    //number of houses
        const int K = costs[0].size(); //number of colors
        
        //let mc(i, j) denote the minimum cost of painting the first i houses, such that
        //the last house (ith house) was painted color j
        vector<int> prevMC(K, 0), nextMC(K, 0);
        
        //base case, cost for painting first 1 houses, with house 0 in desired color
        for (int c=0; c<K; c++)  prevMC[c] = costs[0][c];
        
        for (int h=1; h<N; h++) { //painting house h
            MinColorHeap mch;
            for (int c=0; c<K; c++) { mch.push(ColorInfo(c, prevMC[c]));}
            for (int c=0; c<K; c++) {
                if (c == mch.top().color) continue;
                nextMC[c] = mch.top().cost + costs[h][c]; //paint prev house mch.top().color, and this house c
            }
            int prevColor = mch.top().color;
            mch.pop();
            nextMC[prevColor] = mch.top().cost + costs[h][prevColor];
            prevMC = nextMC;
        }
        int mincost = std::numeric_limits<int>::max();
        for (int c=0; c<K; c++)  {
            if (prevMC[c] < mincost) mincost = prevMC[c];
        }
        return mincost;
    }
};
