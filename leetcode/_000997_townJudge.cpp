class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        // edge case
        if (n == 1 && trust.empty()) return 1;
        
        unordered_map<int, int> tmap;  // x is trusted by how many
        unordered_set<int> trusts;  // x trusts someone
        for (const vector<int>& v : trust) {
            trusts.insert(v[0]);
            tmap[v[1]]++;
        }
        for (const auto& kv: tmap) {
            if (kv.second == n-1 && trusts.find(kv.first) == trusts.end()) return kv.first;
        }
        return -1;
    }
};
