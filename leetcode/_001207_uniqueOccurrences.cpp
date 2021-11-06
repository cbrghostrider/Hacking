class Solution {
public:
    // O(n) time, O(n) space
    bool uniqueOccurrences(vector<int>& arr) {
        std::unordered_map<int, int> counts;
        std::unordered_map<int, int> count_of_counts;
        for (int n : arr) {counts[n]++;}
        for (const auto& kv : counts) {
            count_of_counts[kv.second]++;
        }
        for (const auto& kv : count_of_counts) {
            if (kv.second > 1) return false;
        }
        return true;
    }
};
