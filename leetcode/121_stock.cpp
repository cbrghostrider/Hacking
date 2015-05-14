// simple problem - O(n) runtime, O(1) space
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        int imin=0, imax=0, mprof=0;
        for (int i=1; i<prices.size(); i++) {
            if (prices[imax] <= prices[i]) {
                imax = i;
                int prof = prices[imax] - prices[imin];
                mprof = (prof > mprof) ? prof : mprof;
            }
            if (prices[imin] > prices[i]) { //reset point
                imax = imin = i;
            }
            
        }
        return mprof;
    }
};
