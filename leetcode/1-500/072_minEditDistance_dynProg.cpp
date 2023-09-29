// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// O(mn) time and O(mn) space
// could reduce space down to O(m) or even O(1)
// since I only need a few past entries (would be a bit tricky though!)
class Solution {
public:
    int minDistance(string word1, string word2) {
        const int COST_DEL = 1; //deletion cost
        const int COST_INS = 1; //insertion cost
        const int COST_MUT = 1; //mutation cost
        
        int distance[word1.length()+1][word2.length()+1];
        for (int i=0; i<word2.length()+1; i++) distance[0][i] = i;
        for (int i=0; i<word1.length()+1; i++) distance[i][0] = i;
        
        for (int i=1; i<word1.length()+1; i++) {     //w1
            for (int j=1; j<word2.length()+1; j++) { //w2
                int insw1 = COST_INS + distance[i][j-1];   //inserted same char in w1
                int insw2 = COST_INS + distance[i-1][j];   //inserted same char in w2
                //int delw1 = COST_DEL + distance[i-1][j]; //deleted char from w1 (same cost as insertion into w2)
                //int delw2 = COST_DEL + distance[i][j-1]; //deleted char from w2 (same cost as insertion into w1)
                if (word1[i-1] == word2[j-1]) {
                    int match = distance[i-1][j-1];        //matched both chars
                    distance[i][j] = min(match, min(insw1, insw2));
                } else {
                    int repl  = COST_MUT + distance[i-1][j-1]; //replaced either w1 or w2 char
                    distance[i][j] = min(repl, min(insw1, insw2));
                }
            }
        }
        return distance[word1.length()][word2.length()];
    }
};
