class Solution {
    
    // Some thoughts for non-DP.
    // If there is only one pile, the first person can take all stones and win.
    // If there are two piles:
    //   if each has only 1 stone, then the second person wins (pick 1, pick 1)
    //   if one has 1 stone, and the other has n stones, the first person wins (pick n-1, pick 1, pick 1)
    //   if two piles have n, m stones, then the person to play will try to force the piles to go into 
    //          one of the above eventually.
    // Generally:
    //  Alice/Bob will try to force the game into a "forced-odd-remaining" state at their turn,  
    //        i.e. where odd number of forced moves remain (when they play).
    //  Similarly Alice/Bob will try to get a "forced-even-remaining" state, when the other person has to play.
    // A move is forced, when there is exactly 1 of each remaining in all the piles
    // 
    // (1, 1) bob wins
    // (1, 2) alice wins
    // (2, 2) bob wins
    // (2, 3) alice wins....
    // so with 2 piles, if odd number of total stones, then person playing first wins (and vice versa).
    //
    // (1, 1, n) alice wins
    // (1, 2, 2) alice wins (picks 1, now (2, 2) state, where second person wins)
    // (1, n, m) if (n+m is even, then alice will pick 1 pile of 1 stone and win eventually)
    //           if (n+m is odd, alice will pick 2 from a single pile to keep it odd)
    // (2, 2, 2) alice wins... similarly to above
    //
    // Let n be number of piles with exactly 1 stone.
    // let m be the number of piles with more than 1 stone.
    // and k be TOTAL number of stones "in excess" (i.e. beyond 1 per pile) among all piles.
    //
    // TODO.... non dp
public:
    ///////////////////////////////////////////////////////////////////////////////
    // The following is a top down DP centric solution.
    ///////////////////////////////////////////////////////////////////////////////
    // for given state of piles, game records whether the current player playing at this state will win or lose.
    unordered_map<string, bool> game;
    
    // TOP down DP.
    string signature(vector<int> piles) {  // by value on purpose
        std::sort(piles.begin(), piles.end());
        string sig = "^";
        for (int i=0; i<piles.size(); i++) {
            sig += std::to_string(piles[i]) + "^";
        }
        return sig;
    }
    
    bool play(vector<int>& piles) {
        string sig = signature(piles);
        if (game.find(sig) != game.end()) return game[sig];
        bool ret = false;
        
        for (int i=0; i<piles.size(); i++) {
            if (piles[i] == 0) continue;
            for (int s=1; s<=piles[i]; s++) {
                vector<int> new_piles = piles;
                new_piles[i] -= s;  // take s stones from pile i
                bool other_play = play(new_piles);
                if (other_play == false) {
                    ret = true;  // I found a way to win, by forcing the other person to lose
                                 // Move: pick s stones from pile i
                    break;
                }
            }
            if (ret) { break; }
        }
        
        game[sig] = ret;
        return ret;
    }
    
    bool nimGame(vector<int>& piles) {
        for (int i=piles.size(); i<7; i++) {
            piles.push_back(0);
        }
        
        // Base cases.
        vector<int> base(7, 0);
        for (int i=0; i<7; i++) {
            base[i] = 1;
            string sig = signature(base);
            game[sig] = ((i+1)%2 != 0 ? true : false);
        }
        vector<int> single(7, 0);
        for (int i=0; i<7; i++) {
            single[0] = i+1;
            string sig = signature(single);
            game[sig] = true;
        }
        
        return play(piles);
    }
};
