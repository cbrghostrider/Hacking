// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int w1loc = -1, w2loc = -1;
        int distance = std::numeric_limits<int>::max();
        for (int i=0; i<words.size(); i++) {
            const string& str = words[i];
            if (str == word1) {
                w1loc = i;
                if (w2loc != -1 && abs(w1loc - w2loc) < distance) {
                    distance = abs(w1loc - w2loc);
                }
            } else if (str == word2) {
                w2loc = i;
                if (w1loc != -1 && abs(w1loc - w2loc) < distance) {
                    distance = abs(w1loc - w2loc);
                }
            }
        }
        return distance;
    }
};
