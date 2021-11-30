class Solution {
public:
    // O(nlogn) time, O(n) space.
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freqs;
        for (string& word : words) {freqs[word]++;}
        
        vector<pair<string, int>> word_freq;
        for (const auto& kv : freqs) {word_freq.push_back(make_pair(kv.first, kv.second));}
        std::sort(word_freq.begin(), word_freq.end(), 
                  [](const pair<string, int>& lhs, const pair<string, int>& rhs) -> bool {
            if (lhs.second != rhs.second) {return lhs.second > rhs.second;}
            return lhs.first < rhs.first;
        });
        vector<string> ans;
        for (int i=0; i<k; i++) {
            ans.push_back(word_freq[i].first);
        }
        return ans;
    }
};
