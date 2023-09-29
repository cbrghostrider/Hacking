// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
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
