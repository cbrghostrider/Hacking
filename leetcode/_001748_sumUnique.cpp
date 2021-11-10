class Solution {
public:
    // O(n) space, O(n) time.
    int sumOfUnique(vector<int>& nums) {
        unordered_map<int, int> elems;
        for (int n : nums) elems[n]++;
        int sum = 0;
        for (const auto& kv : elems) {
            if (kv.second == 1) sum += kv.first;
        }
        return sum;
    }
};
