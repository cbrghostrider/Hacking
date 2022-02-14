struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {
        return (r == rhs.r && c == rhs.c);
    }
    bool operator<(const Coord& rhs) const {
        if (r != rhs.r) return r < rhs.r;
        if (c != rhs.c) return c < rhs.c;
        return false;
    }
};

template<>
struct hash<Coord> {
size_t operator()(const Coord& coord) const {
    return ((coord.r << 16) | (coord.c));
}
};

class Solution {
    int R,C;
    
    // key: coord
    // value: my leader
    unordered_map<Coord, int> coord_to_leader;
        
    // key: leader#
    // value: all the coords that belong to it
    unordered_map<int, set<Coord>> leader_group;
    
    // labels for leaders will be handed out one by one
    int next=0;
    
    void mergeLeaders(int leader1, int leader2) { 
        if (leader1 == leader2) return;
        
        const set<Coord>& g1 = leader_group[leader1];
        const set<Coord>& g2 = leader_group[leader2];
        
        // optimization for group size <= 5
        if (g2.size() <= 5) {
            for (const auto& cc : g2) {
                coord_to_leader[cc] = leader1;
                leader_group[leader1].insert(cc);                
            }
            leader_group.erase(leader2);
            return;
        }
        
        set<Coord> combo;
        std::set_union(g1.begin(), g1.end(), g2.begin(), g2.end(), std::inserter(combo, combo.begin()));
        
        if (g1.size() >= g2.size()) {
            for (const Coord& crd : g2) {
                coord_to_leader[crd] = leader1;
            }
            leader_group.erase(leader2);
            leader_group[leader1] = combo;
        } else {
            for (const Coord& crd : g1) {
                coord_to_leader[crd] = leader2;
            }
            leader_group.erase(leader1);
            leader_group[leader2] = combo;
        }
    }
    
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        R=m;
        C=n;        
        
        vector<int> ans;
        for (const vector<int>& pos : positions) {
            int leader = next++;
            Coord me = {pos[0], pos[1]};
            if (coord_to_leader.find(me) != coord_to_leader.end()) {
                ans.push_back(leader_group.size());
                continue;
            }
            
            coord_to_leader[me] = leader;
            leader_group[leader] = {me};
            
            vector<Coord> neighs = {
                {me.r-1, me.c}, {me.r, me.c-1},
                {me.r+1, me.c}, {me.r, me.c+1},
            };
            
            for (const Coord& ne : neighs) {
                if (ne.r < 0 || ne.r == R || ne.c < 0 || ne.c == C) continue;     // out of bounds
                if (coord_to_leader.find(ne) == coord_to_leader.end()) continue;  // water
                int my_leader = coord_to_leader[me];
                int ne_leader = coord_to_leader[ne];
                mergeLeaders(ne_leader, my_leader);
            }
            ans.push_back(leader_group.size());
        }
        
        return ans;
    }
};
