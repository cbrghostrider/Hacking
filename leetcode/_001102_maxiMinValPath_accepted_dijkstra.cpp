struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {
        return (r == rhs.r && c == rhs.c);
    }
};

template<>
struct hash<Coord> {
size_t operator()(const Coord& key) const {
  return ((key.r << 16) | (key.c));
}
};

class Solution {

    unordered_map<Coord, unordered_map<Coord, int>> graph;
    int R, C;
    Coord start, end;
    
    void buildGraph(const vector<vector<int>>& grid) {
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                Coord crd = {r, c};
                if (r != 0)   {  Coord cn = {r-1, c}; graph[crd][cn] = grid[r-1][c]; }
                if (r != R-1) {  Coord cs = {r+1, c}; graph[crd][cs] = grid[r+1][c]; }
                if (c != 0)   {  Coord cw = {r, c-1}; graph[crd][cw] = grid[r][c-1]; }
                if (c != C-1) {  Coord ce = {r, c+1}; graph[crd][ce] = grid[r][c+1]; }
            }
        }
    }
    
    int dijkstra(const vector<vector<int>>& grid) {
        auto comp = [](const pair<Coord, int>& lhs, const pair<Coord, int>& rhs) -> bool {
            return lhs.second < rhs.second;
        };
        
        priority_queue<pair<Coord, int>, vector<pair<Coord, int>>, decltype(comp)> pq(comp);
        unordered_map<Coord, bool> done;
        unordered_map<Coord, int> distance;
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                distance[{r, c}] = std::numeric_limits<int>::min();
                done[{r, c}] = false;
            }
        }
        pq.push({{0, 0}, grid[0][0]});
        
        while (!pq.empty()) {
            auto elem = pq.top(); pq.pop();
            Coord crd = elem.first;
            int dist = elem.second;
            if (done[crd]) {continue;}
            if (distance[crd] > dist) {continue;}
            distance[crd] = dist;
            done[crd] = true;
            
            if (crd.r != 0)   { pq.push({{crd.r-1, crd.c}, std::min(dist, grid[crd.r-1][crd.c])}); }
            if (crd.r != R-1) { pq.push({{crd.r+1, crd.c}, std::min(dist, grid[crd.r+1][crd.c])}); }
            if (crd.c != 0)   { pq.push({{crd.r, crd.c-1}, std::min(dist, grid[crd.r][crd.c-1])}); }
            if (crd.c != C-1) { pq.push({{crd.r, crd.c+1}, std::min(dist, grid[crd.r][crd.c+1])}); }
        }
        return distance[end];
    }
public:
    // Using dijkstra
    int maximumMinimumPath(vector<vector<int>>& grid) {
        R = grid.size();
        C = grid[0].size();
        start = {0, 0};
        end = {R-1, C-1};
        
        buildGraph(grid);
        return dijkstra(grid);        
    }
};
