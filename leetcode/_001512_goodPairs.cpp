class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        std::unordered_map<int, int> counts;
        int ans = 0;
        for (int n : nums) {
            ans += counts[n];
            counts[n]++;
        }
        return ans;
    }
};
