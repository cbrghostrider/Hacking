class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_set<int> found;
        for (int n : nums) {
            if (found.find(n) != found.end()) return n;
            found.insert(n);
        }
        return -1;
    }
};
