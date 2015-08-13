// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class WordDistance {
    unordered_map<string, unordered_set<int>> wordToLocations; //tells us where various words are found
public:
    WordDistance(vector<string>& words) {
        for (int i=0; i<words.size(); i++) {
            auto it = wordToLocations.find(words[i]);
            if (it == wordToLocations.end()) {
                wordToLocations.insert(make_pair(words[i], unordered_set<int>()));
            }
            wordToLocations[words[i]].insert(i);
        }
    }

    int shortest(string word1, string word2) {
        int minval = std::numeric_limits<int>::max();
        for (const int& w1 : wordToLocations[word1]) {
            for (const int& w2 : wordToLocations[word2]) {
                if (w1 == w2) continue;
                int cand = std::abs(w1 - w2);
                if (cand < minval) {
                    minval = cand;
                }
            }
        }
        return (std::numeric_limits<int>::max() == minval ? -1 : minval);
    }
};

class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        WordDistance wd(words);
        return wd.shortest(word1, word2);
    }
};


