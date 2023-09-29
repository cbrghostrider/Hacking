class Solution {
public:
    // O(n) time, O(n) space.
    string kthDistinct(vector<string>& arr, int k) {
        std::unordered_map<string, int> counts;
        for (string str : arr) counts[str]++;
        int num = 0;
        for (string str : arr) {
            if (counts[str] == 1) {
                num++;
                if (num == k) return str;
            }
        }
        return "";
    }
};
