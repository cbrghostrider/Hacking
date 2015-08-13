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
                int cand = std::abs(w1 - w2);
                if (cand < minval) {
                    minval = cand;
                }
            }
        }
        return (std::numeric_limits<int>::max() == minval ? -1 : minval);
    }

};

// Your WordDistance object will be instantiated and called as such:
// WordDistance wordDistance(words);
// wordDistance.shortest("word1", "word2");
// wordDistance.shortest("anotherWord1", "anotherWord2");
