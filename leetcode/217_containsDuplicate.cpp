class Solution {
    unordered_set<int> hashTable;
public:
    bool containsDuplicate(vector<int>& nums) {
        if (nums.size() <= 1) return false;
        for (int& n : nums) {
            if (hashTable.find(n) != hashTable.end()) return true;
            hashTable.insert(n);
        }
        return false;
    }
};
