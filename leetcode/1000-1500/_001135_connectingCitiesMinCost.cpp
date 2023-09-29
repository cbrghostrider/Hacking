class Solution {
    vector<int> leaders;
    vector<int> sizes;
    
    // O(1) time.
    void uf_union(int leader1, int leader2) {
        if (leader1 == leader2) return;
        if (sizes[leader1] >= sizes[leader2]) {
            leaders[leader2] = leader1;
            sizes[leader1] += sizes[leader2];
        } else {
            leaders[leader1] = leader2;
            sizes[leader2] += sizes[leader1];            
        }
    }
    
    // O(log n) time.
    int uf_find(int index) {
        while (index != leaders[index]) {
            index = leaders[index];
        }
        return index;
    }
    
public:
    // O(n log n) time, O(n) space.
    int minimumCost(int n, vector<vector<int>>& connections) {
        min_heap = MinHeap(comp);
        
        for (int i=1; i<=n; i++) {
            leaders.push_back(i-1);
            sizes.push_back(i);
        }
        
        std::sort(connections.begin(), connections.end(), [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            return (lhs[2] < rhs[2]);
        });
        
        int cost=0;
        for (const vector<int>& edge : connections) {
            int from=edge[0]-1;
            int to = edge[1]-1;
            int my_cost = edge[2];
            
            int f_leader = uf_find(from);
            int t_leader = uf_find(to);
            if (f_leader == t_leader) continue;
            
            cost += my_cost;
            uf_union(f_leader, t_leader);
        }
        
        int count=0;
        for (int i=0; i<leaders.size(); i++) {
            if (i == leaders[i]) count++;
        }
        if (count > 1) return -1;
        return cost;
    }
};
