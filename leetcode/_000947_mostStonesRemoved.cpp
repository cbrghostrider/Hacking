class Solution {
    vector<int> leaders;
    vector<int> sizes;
    
    // O(log n) time.
    int uf_find(int index) {
        while (index != leaders[index]) {
            index = leaders[index];
        }
        return index;
    }
   
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
public:
    
    // O(n log n) time, O(n) space.
    int removeStones(vector<vector<int>>& stones) {        
        for (int i=0; i<stones.size(); i++) {
            leaders.push_back(i);
            sizes.push_back(1);
        }
        
        unordered_map<int, int> x_to_group, y_to_group;
        for (int i=0; i<stones.size(); i++) {
            int x = stones[i][0], y = stones[i][1];
            auto find_x = x_to_group.find(x), end_x = x_to_group.end();
            auto find_y = y_to_group.find(y), end_y = y_to_group.end();
            if (find_x != end_x && find_y != end_y) {
                uf_union(uf_find(x_to_group[x]), uf_find(i));
                uf_union(uf_find(y_to_group[y]), uf_find(i));
            } else if (find_x != end_x) {
                uf_union(uf_find(x_to_group[x]), uf_find(i));   
                y_to_group[y] = i;
            } else if (find_y != end_y) {
                x_to_group[x] = i;
                uf_union(uf_find(y_to_group[y]), uf_find(i));
            } else {
                x_to_group[x] = i;
                y_to_group[y] = i;
            }
        }
        
        int num_groups=0;
        for (int i=0; i<stones.size(); i++) {
            if (i == leaders[i]) {
                num_groups++;
            }
        }
        return stones.size()-num_groups;
    }
};
