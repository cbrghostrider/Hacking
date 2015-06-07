// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
private:
    template<typename Iterator>
    vector<int> computeCumulativeSum_(Iterator from,Iterator to) {
        vector<int> retval;
        int cumuSum=0;
        while (from != to) {
            cumuSum += *from;
            retval.push_back(cumuSum);
            from = from + 1;
        }
        return retval;
    }
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        
        //from start to index i at any step
        vector<int> cumulativeSum = computeCumulativeSum_(nums.begin(), nums.end());
        vector<int> revCumulativeSum = computeCumulativeSum_(nums.rbegin(), nums.rend());
        std::reverse(revCumulativeSum.begin(), revCumulativeSum.end());
        
        int max    = cumulativeSum[0];
        int revMax = revCumulativeSum[0];
        int from=0, to=0, revInd = 0;
        //keep track of current best candidate [from, to] and corresponding max
        //also keep track of revInd, the index where the reverseCumulativeSum so far has peaked
        //scan from  L -> R, considering one new element at a time at index ind
        //if [revInd, ind] is higher than current max, this is new candidate
        for (int ind=1; ind<nums.size(); ind++) {
            if (revCumulativeSum[ind] > revMax) {
                revMax = revCumulativeSum[ind];
                revInd = ind;
            }
            if ((max < (cumulativeSum[ind] - cumulativeSum[revInd-1]))){
                from = revInd; 
                to = ind;
                max = cumulativeSum[to] - cumulativeSum[from-1];
            }
        }
        return max;
    }
};
