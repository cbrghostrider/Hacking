struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {
        return (r == rhs.r && c == rhs.c);
    }
    bool operator!=(const Coord& rhs) const {
        return !(*this == rhs);
    }
    bool operator<(const Coord& rhs) const {
        if (r != rhs.r) return r < rhs.r;
        return c < rhs.c;
    }
};
template<>
struct hash<Coord> {
size_t operator()(const Coord& key) const {
    return ((key.r << 16) | (key.c));
}
};
class Solution {
    int R, C;

    // returns all nodes reachable from the start nodes, taking height into account
    set<Coord> bfs(const vector<vector<int>>& heights, std::queue<Coord>& q) {
        set<Coord> ans;
        while (!q.empty()) {
            auto elem=q.front(); q.pop();
            ans.insert(elem);
            
            vector<Coord> neighs = {
                {elem.r-1, elem.c}, {elem.r+1, elem.c}, {elem.r, elem.c-1}, {elem.r, elem.c+1}
            };
            for (const Coord& neigh : neighs) {
                if (neigh.r < 0 || neigh.r >= R || neigh.c < 0 || neigh.c >= C) continue;
                if (ans.find(neigh) != ans.end()) continue;
                if (neigh.r == 0 && neigh.c==1) {
                    int a=0;
                }
                if (heights[neigh.r][neigh.c] < heights[elem.r][elem.c]) continue;
                ans.insert(neigh);
                q.push(neigh);
            }
        }
        return ans;
    }
    
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        R=heights.size();
        C=heights[0].size();
        
        std::queue<Coord> pq, aq;
        for (int r=0; r<R; r++) {
            pq.push( {r, 0});
            aq.push({r, C-1});
        }
        for (int c=0; c<C; c++) {
            pq.push( {0, c});
            aq.push({R-1, c});
        }
        std::set<Coord> pacific  = bfs(heights, pq);
        std::set<Coord> atlantic = bfs(heights, aq);
        
        std::vector<Coord> chosen;
        std::set_intersection(pacific.begin(), pacific.end(), atlantic.begin(), atlantic.end(),
                             std::back_inserter(chosen));
        
        vector<vector<int>> ans;
        for (const Coord& crd : chosen) {
            ans.push_back({crd.r, crd.c});
        }
        return ans;
    }
    
    
};
