class Solution {
public:
    // O(n) time, O(n) space.
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        unordered_map<int, vector<int>> adj_list;
        
        for (const auto& ap : adjacentPairs) {
            adj_list[ap[0]].push_back(ap[1]);
            adj_list[ap[1]].push_back(ap[0]);
        }
        
        int source=-1;
        for (const auto& kv : adj_list) {
            if (kv.second.size() == 1) {
                source = kv.first;
                break;
            }
        }
        
        unordered_set<int> visited;
        vector<int> ans;
        ans.push_back(source);
        visited.insert(source);
        while (ans.size() != adj_list.size()) {
            for (int n : adj_list[source]) {
                if (visited.find(n) != visited.end()) continue;
                source = n;
                ans.push_back(n);
                visited.insert(n);
                break;
            }
        }
        return ans;
    }
};
