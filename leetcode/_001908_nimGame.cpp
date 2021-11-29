class Solution {
    
     // EDIT: For non-DP solution, refer to sprague-grundy theorem.
     // FML...
     // https://cp-algorithms.com/game_theory/sprague-grundy-nim.html
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
