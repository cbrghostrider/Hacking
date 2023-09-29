class Solution {

public:
    // O(n^2) time, O(n) space
    bool divisorGame(int n) {
        // 0 denotes loss if that index comes up on board for current player
        vector<int> results(n+1, 0);
        // n==0 or n==1 has no moves possible since 0<x<n
        
        for (int i=2; i<=n; i++) {
            // pick all xs which are a divisor between [1, i-1] inclusive, and see if you can force a win
            bool can_win = false;
            for (int x=i-1; x>=1; x--) {
                if (i % x != 0) continue;
                int diff = i-x;
                if (results[diff] == 0) {
                    can_win = true;
                    break;
                }
            }
            results[i] = (can_win ? 1 : 0);
        }
        
        return results[n];
    }
};
