// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// Forward declaration of the knows API.
bool knows(int a, int b);

class Solution {
    vector<int> potCelebs;
public:
    int findCelebrity(int n) {
        //return findCelebrity(0, n-1);
        for (int i=0; i<n; i++) {
            int j=0;
            for (j=0; j<n; j++) {
                if (i != j && knows(i, j)) break;
            }
            if (j == n) potCelebs.push_back(i); //i knows no one
        }
        
        for (int i=0; i<potCelebs.size(); i++) {
            int j=0;
            for (j=0; j<n; j++) {
                if (potCelebs[i] != j && !knows(j, potCelebs[i])) break;
            }
            if (j == n) return potCelebs[i];
        }
        return -1;
    }
};
