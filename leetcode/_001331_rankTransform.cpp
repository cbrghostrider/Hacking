class Solution {
public:
    
    // O(nlogn) time, O(n) space.
    vector<int> arrayRankTransform(vector<int>& arr) {
        int rank = 1;
        
        vector<int> ans = arr;
        std::sort(ans.begin(), ans.end());
        
        unordered_map<int, int> ranks;
        for (int n : ans) {
            if (ranks[n] == 0) {
                ranks[n] = rank++;
            }
        }
        for (int i=0; i<arr.size(); i++) {
            ans[i] = ranks[arr[i]];
        }
        return ans;
    }
};
