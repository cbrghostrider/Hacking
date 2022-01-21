class Solution {
    // key: cell#
    // val: neigh cell#
    unordered_map<int, vector<int>> graph;
    int R, C;
    
    std::function<bool(int, int, int)> cmp = [](bool flip, int lhs, int rhs) -> bool {
        return (flip ? lhs >= rhs : lhs <= rhs);
    };

    
    // key: crd represented as an int(r << 16 | C)
    // val: the cell
    unordered_map<int, int> crds_to_cell;
    unordered_map<int, pair<int, int>> cell_to_crd;
    
    bool impossible = false;
    
    int crdToInt(int r, int c) {
        return ((r << 16) | (c));
    }
    
    void init() {
        bool flip=false;
        int cell=1;
        for (int r=R-1; r>=0; r--) {
            int delta = flip ? -1 : 1;
            int start = flip ? C-1 : 0;
            int end = flip ? 0 : C-1;
            for (int c=start; cmp(flip, c, end); c += delta) {
                int crd = crdToInt(r, c);
                cell_to_crd[cell] = {r, c};
                crds_to_cell[crd] = cell++;                
            }
            flip = !flip;
        }        
    }
    
    void buildGraph(const vector<vector<int>>& board) {
        bool flip=false;
        int cell=1;        
        for (int r=R-1; r>=0; r--) {
            int delta = flip ? -1 : 1;
            int start = flip ? C-1 : 0;
            int end = flip ? 0 : C-1;
            for (int c=start; cmp(flip, c, end); c += delta) {
                int crd = crdToInt(r, c);
                int cell = crds_to_cell[crd];
                
                for (int d=1; d<=6; d++) {
                    if (cell + d > R*C) {break;}
                    
                    int neigh_cell = cell + d;
                    pair<int, int> ncrd = cell_to_crd[neigh_cell];
                    if (board[ncrd.first][ncrd.second] != -1) {
                        int new_neigh_cell = board[ncrd.first][ncrd.second];
                        neigh_cell = new_neigh_cell;
                        ncrd = cell_to_crd[neigh_cell];                        
                    }
                    
                    graph[cell].push_back(neigh_cell);
                }                
            }
            flip = !flip;
        }
    }
    
    int bfs() {
        int source = 1;
        const int dest = R*C;
        
        queue<pair<int, int>> q;
        q.push({source, 0});
        unordered_set<int> gone;
        gone.insert(source);
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            if (elem.first == dest) {return elem.second;}
            
            for (int ncell : graph[elem.first]) {
                if (gone.find(ncell) != gone.end()) continue;
                gone.insert(ncell);
                q.push({ncell, elem.second+1});
            }
        }
        return -1;
    }
    
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        R = board.size();
        C = board[0].size();
        
        init();
        buildGraph(board);
        if (impossible) return -1;
        int ans = bfs();
        
        return ans;
    }
};
