class Solution {
    
public:
    // Conceptually....
    bool canWinNim2(int n) {
        vector<bool> can_win(n+1, false);
        can_win[1] = can_win[2] = can_win[3] = true;
        for (int i=4; i<=n; i++) {
            if (can_win[i-1] == true && can_win[i-2] == true && can_win[i-3] == true) {
                can_win[i] = false;
            } else {
                can_win[i] = true;
            }
        }
        return can_win[n];
    }
    // Therefore: 1, 2, 3 -> win
    //            4 -> loss
    //            5, 6, 7 -> win
    //            8 -> loss
    //            and so on...
    bool canWinNim(int n) {
        return (n % 4);
    }
};
