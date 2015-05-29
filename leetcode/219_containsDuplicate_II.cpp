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
