class Solution {
    struct Coord {
        int r=0;
        int c=0;
        bool operator>(const Coord& rhs) const {  // used for random tiebreaking in heap
            if (r != rhs.r) {return r > rhs.r;}
            return c > rhs.c;
        }
    };
    struct Info {
        Coord me;
        int max_diff=0;  // max abs diff in elevation for the entire path from src to "me"        
    };
        
    std::function<bool(const Info&, const Info&)> comp = [](const Info& lhs, const Info& rhs) -> bool {
        if (lhs.max_diff != rhs.max_diff) {return lhs.max_diff > rhs.max_diff;}
        return lhs.me > rhs.me;
    };
    using MinHeap=priority_queue<Info, vector<Info>, decltype(comp)>;    
    
    unordered_set<int> visited;
    
    int signature(int r, int c) {
        return ((r << 16) | (c));
    }
    
    void markVisited(int r, int c) {
        int sig = signature(r, c);
        visited.insert(sig);
    }
    
    bool isVisited(int r, int c) {
        int sig = signature(r, c);
        return (visited.find(sig) != visited.end());
    }
    
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        const int R=heights.size();
        const int C=heights[0].size();        
        
        MinHeap min_heap(comp);
        min_heap.push({{0, 0}, 0});
        
        
        while (!min_heap.empty()) {
            auto elem = min_heap.top(); min_heap.pop();
            Coord crd = elem.me;
            if (isVisited(crd.r, crd.c)) {continue;}  // stale heap element
            if (crd.r == R-1 && crd.c == C-1) {return elem.max_diff;}            
            markVisited(crd.r, crd.c);
            
            vector<Coord> neighs = {
                {crd.r-1, crd.c}, {crd.r+1, crd.c}, {crd.r, crd.c-1}, {crd.r, crd.c+1}
            };
            for (const Coord& neigh : neighs) {
                int r = neigh.r, c = neigh.c;
                if (r < 0 || r == R || c < 0 || c == C) {continue;}  // out of bounds
                if (isVisited(r, c)) {continue;}
                
                int rel_diff = std::abs(heights[crd.r][crd.c] - heights[r][c]);
                min_heap.push({neigh, std::max(rel_diff, elem.max_diff)});
            }
        }
        return -1;  // should not get here
    }
};
