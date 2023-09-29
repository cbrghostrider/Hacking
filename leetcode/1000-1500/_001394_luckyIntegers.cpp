class Solution {
public:
    // O(n) time, O(n) space.
    int findLucky(vector<int>& arr) {
        std::unordered_map<int, int> freqs;
        for (int n : arr) freqs[n]++;
        int lucky = -1;
        for (const auto& kv : freqs) {
            if (kv.first == kv.second) {
                if (kv.first > lucky) lucky = kv.first;
            }
        }
        return lucky;
    }
};
