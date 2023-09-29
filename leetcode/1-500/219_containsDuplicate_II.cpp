// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    unordered_set<int> hashTable;
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        if (nums.size() == 0 || k <=0 ) return false;
        for (int i=0; i<=k && i<nums.size() ;i++) {
            if (hashTable.find(nums[i]) != hashTable.end()) return true;
            hashTable.insert(nums[i]);
        }
        for (int i=k+1; i<nums.size(); i++) {
            hashTable.erase(nums[i-(k+1)]);
            if (hashTable.find(nums[i]) != hashTable.end()) return true;
            hashTable.insert(nums[i]);
        }
        return false;
    }
};
