class Solution {
public:
    enum Pick {
        NONE=0,
        LEFT=1,
        RIGHT=2
    };
    enum Winner {
        TIE=0,
        ALICE=1,
        BOB=2,
    };
    struct Choice {
        Pick pick;
        Winner winner;
        int alice_has=0;  // At this point, Alice will get these many total stones.
        int bob_has=0;    // At this point, Bob will get these many total stones.
    };
    
    bool stoneGame(vector<int>& piles) {
        // choices stores the value of final stones along with the optimal choice
        // indexed by [pile-size][starting-index]
        vector<vector<Choice>> 
            choices(piles.size()+1, vector<Choice>(piles.size(), {NONE, TIE, 0, 0}));
        
        // We are told that pile size is ultimately even.
        // So odd scenario, we optimize for Bob, even scenario, we optimize for Alice.
        
        // Base case: All piles of size 1 (odd scenario).
        for (int i=0; i<piles.size(); i++) {
            choices[1][i] = {NONE, BOB, 0, piles[i]};
        }
        
        for (int psz=2; psz<=piles.size(); psz++) {
            for (int i=0; i<piles.size() && (i+psz) <= piles.size(); i++) {
                if (psz % 2 == 0) {  // even scenario: Alice gets to choose
                    int choose_left_alice_has = piles[i] + choices[psz-1][i+1].alice_has;
                    int choose_left_bob_has = choices[psz-1][i+1].bob_has;
                    int choose_right_alice_has = choices[psz-1][i].alice_has + piles[i+psz-1];
                    int choose_right_bob_has = choices[psz-1][i].bob_has;
                    
                    int choose_left_diff = (choose_left_alice_has - choose_left_bob_has);
                    int choose_right_diff = (choose_right_alice_has - choose_right_bob_has);
                    
                    if (choose_left_diff >= choose_right_diff) {
                        Winner win = (choose_left_diff > 0 ? ALICE : BOB);
                        choices[psz][i] = {LEFT, win, choose_left_alice_has, choose_left_bob_has};
                    } else {
                        Winner win = (choose_right_diff > 0 ? ALICE : BOB);
                        choices[psz][i] = {RIGHT, win, choose_right_alice_has, choose_right_bob_has};
                    }
                } else {  // odd scenario: Bob gets to choose
                    int choose_left_bob_has = piles[i] + choices[psz-1][i+1].bob_has;
                    int choose_left_alice_has = choices[psz-1][i+1].alice_has;
                    int choose_right_bob_has = choices[psz-1][i].bob_has + piles[i+psz-1];
                    int choose_right_alice_has = choices[psz-1][i].alice_has;

                    int choose_left_diff = (choose_left_bob_has - choose_left_alice_has);
                    int choose_right_diff = (choose_right_bob_has - choose_right_alice_has);
                    
                    if (choose_left_diff >= choose_right_diff) {
                        Winner win = (choose_left_diff > 0 ? BOB : ALICE);
                        choices[psz][i] = {LEFT, win, choose_left_alice_has, choose_left_bob_has};
                    } else {
                        Winner win = (choose_right_diff > 0 ? BOB : ALICE);
                        choices[psz][i] = {RIGHT, win, choose_right_alice_has, choose_right_bob_has};
                    }
                }
            }
        }
        
        return (choices[piles.size()][0].alice_has > choices[piles.size()][0].bob_has);
    }
};
