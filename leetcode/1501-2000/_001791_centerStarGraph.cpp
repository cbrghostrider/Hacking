class Solution {
    unordered_map<int, int> conns;
public:
    int findCenter(vector<vector<int>>& edges) {
        for (const auto& e : edges) {
            conns[e[0]]++;
            conns[e[1]]++;
        }
        for (const auto& kv : conns) {
            if (kv.second > 1) return kv.first;
        }
        return -1;
    }
};
