// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//O(n^2) time and O(n) space, where n is number of elements at the bottom of the triangle
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        //dynamic programming cache
        vector<int> cache[2];
        cache[0] = cache[1] = vector<int>(triangle[triangle.size()-1].size(), 0);
        int prev=0, next=1;
        
        //base case, bottom-most row
        cache[prev] = triangle[triangle.size()-1];
        
        //dynamic programming loops
        for (int row=triangle.size()-2; row>=0; row--) {
            for (int col=0; col<triangle[row].size(); col++) {
                int cand1 = triangle[row][col] + cache[prev][col];
                int cand2 = triangle[row][col] + cache[prev][col+1];
                cache[next][col] = (cand1 < cand2) ? cand1 : cand2;
            }
            prev = 1-prev;
            next = 1-next;
        }
        return cache[prev][0];
    }
};
