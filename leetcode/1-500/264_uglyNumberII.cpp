// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int nthUglyNumber(int n) {
        deque<int> uglies = {0, 1, 2, 3};
        if (n <= 0) return 0;
        if (n <= 3) return uglies[n];
        
        int u2p=1, u3p=1, u5p=1; //points to indices
        
        int count = 3;
        int num = 3;
        while (count < n) {
            int cand2 = uglies[u2p] * 2;
            int cand3 = uglies[u3p] * 3;
            int cand5 = uglies[u5p] * 5;
            int newnum;
            if (cand2 <= cand3 && cand2 <= cand5) {
                newnum = cand2;  u2p++;
            } else if (cand3 <= cand2 && cand3 <= cand5) {
                newnum = cand3; u3p++;
            } else {
                newnum = cand5; u5p++;
            }
            if (newnum <= num) continue;
            num = newnum;
            uglies.push_back(num);
            count++;
            
            //optional to reduce space requirement, pop numbers that won't be needed
            int popAmount = std::min(u2p, std::min(u3p, u5p));
            u2p -= popAmount; u3p -= popAmount; u5p -= popAmount;
            while (popAmount != 0) {uglies.pop_front(); popAmount--; } 
        }
        return num;
    }
};
