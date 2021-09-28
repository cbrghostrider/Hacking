class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        std::unordered_set<int> ht(arr.begin(), arr.end());
        int num_zeros = 0;
        for (const int val : arr) {
            if (val == 0) {
                num_zeros++;
            }
            if (val != 0 && ht.find(2 * val) != ht.end()) {
                return true;
            }
        }
        return (num_zeros >= 2);
    }
};
