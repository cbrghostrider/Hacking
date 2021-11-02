class Solution {
    std::unordered_map<int, vector<int>> indices;
public:
    // O(n) time, O(n) space
    vector<int> anagramMappings(vector<int>& nums1, vector<int>& nums2) {
        for (int i=0; i<nums2.size(); i++) {
            indices[nums2[i]].push_back(i);
        }
        vector<int> ans;
        for (int n : nums1) {
            ans.push_back(indices[n].back());
            indices[n].pop_back();
        }
        return ans;
    }
};
