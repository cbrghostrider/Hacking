class Solution {
public:
    // O(n log n) time, O(n) space.
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        
        unordered_map<int, int> freqs;
        for (int n : arr) { freqs[n]++; }
        
        // (val, freq)
        vector<pair<int, int>> farr;
        for (const auto& kv : freqs) {farr.push_back({kv.first, kv.second});}
        
        std::sort(farr.begin(), farr.end(), [](const pair<int, int>& lhs, const pair<int, int>& rhs)->bool {
            if (lhs.second != rhs.second) return lhs.second < rhs.second;
            return lhs.first < rhs.first;
        });
        
        for (pair<int, int> vf : farr) {
            if (vf.second > k) {break;}
            k -= vf.second;
            freqs.erase(vf.first);
        }
        return freqs.size();
    }
};
