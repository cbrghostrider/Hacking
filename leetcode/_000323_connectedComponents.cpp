class Solution {
    vector<int> leaders;
    vector<int> sizes;
    
    // returns the name of the leader for this group
    // O(log n) time.
    int find(int node) {
        while (leaders[node] != node) {
            node = leaders[node];
        }
        return node;
    }
    
    // O(1) time union of two groups into one.
    void unite(int leader1, int leader2) {
        if (sizes[leader1] > sizes[leader2]) {
            leaders[leader2] = leader1;
        } else {
            leaders[leader1] = leader2;
        }
    }

    
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        for (int i=0; i<n; i++) {
            leaders.push_back(i);
            sizes.push_back(1);
        }
        
        for (const auto& edge : edges) {
            int l1 = find(edge[0]);
            int l2 = find(edge[1]);
            unite(l1, l2);
        }
        
        int count=0;
        for (int i=0; i<n; i++) {
            if (leaders[i] == i) {count++;}
        }
        return count;
    }
};
