class Solution {
    std::unordered_map<string, std::set<string>> similars;
public:
    bool areSentencesSimilar(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {
        if (sentence1.size() != sentence2.size()) return false;
        for (const auto& kv : similarPairs) {
            similars[kv[0]].insert(kv[1]);
            similars[kv[1]].insert(kv[0]);
        }
        for (int i=0; i<sentence1.size(); i++) {
            const string& word1 = sentence1[i];
            const string& word2 = sentence2[i];
            if (word1 == word2) continue;
            if (similars[word1].find(word2) != similars[word1].end()) continue;
            if (similars[word2].find(word1) != similars[word2].end()) continue;
            return false;
        }
        return true;
    }
};
