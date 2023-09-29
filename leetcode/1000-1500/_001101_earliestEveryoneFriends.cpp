class Solution {
    vector<int> leaders;
    vector<int> sizes;
        
    int uf_find(int index) {
        while (index != leaders[index]) {
            index = leaders[index];
        }
        return index;
    }
    
    void uf_union(int leader1, int leader2) {
        if (leader1 == leader2) return;
        if (sizes[leader1]>=sizes[leader2]) {
            leaders[leader2] = leader1;
            sizes[leader1] += sizes[leader2];
        } else {
            leaders[leader1] = leader2;
            sizes[leader2] += sizes[leader1];            
        }
    }
    
public:
    int earliestAcq(vector<vector<int>>& logs, int n) {
        std::sort(logs.begin(), logs.end(), [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs[0] != rhs[0]) return lhs[0] < rhs[0];
            return false;
        });
        
        for (int i=0; i<n; i++) {
            leaders.push_back(i);
            sizes.push_back(1);
        }
        
        for (const auto& entry : logs) {
            int time = entry[0];
            int l1 = uf_find(entry[1]);
            int l2 = uf_find(entry[2]);
            uf_union(l1, l2);
            if (sizes[uf_find(l1)] == n) return time;
        } 
        
        return -1;
    }
};
