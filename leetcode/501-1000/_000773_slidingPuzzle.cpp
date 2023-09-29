// Convert this into a graph search problem.
// Then run BFS to find the min number of moves.
//
// Essentially each "node" in the graph is one representation of the board
// Nodes connect to each other if a single swap can go from one node to the other
// Then start at the starting node, ending node is the one represented by end state.
// Run BFS.
//
// There are 6! permutations for nodes.
class Solution {
    unordered_map<string, int> board_to_node;
    int next_node=0;  // allocate nodes in order
    const int R=2;
    const int C=3;
    
    unordered_map<int, unordered_set<int>> adj_list;
    
    using Board=vector<vector<int>>;
    Board target = {{1, 2, 3}, {4, 5, 0}};
    Board source;
    
    string getRepr(const Board& board) {
        string repr;
        for (int r=0;r<R; r++) {
            for (int c=0; c<C; c++) {
                repr += to_string(board[r][c]) + ";";
            }
        }
        return repr;
    }
    
    // (r, c) is the next cell to populate
    // choices are the things that can go in that place
    vector<Board> generateBoards(Board board, int r, int c, unordered_set<int> choices) {
        if (choices.empty()) return {board};        
        
        int r2=0, c2=0;
        if (c == C-1) {
            r2=r+1; c2=0;
        } else {
            r2=r; c2=c+1;
        }
        
        vector<Board> ans;
        for (int ch : choices) {
            unordered_set<int> choices2 = choices;
            choices2.erase(ch);
            board[r][c] = ch;

            vector<Board> recurse = generateBoards(board, r2, c2, choices2);
            ans.insert(ans.end(), recurse.begin(), recurse.end());
        }
        return ans;
    }
    
    pair<int, int> locateZero(const Board& board) {
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (board[r][c] == 0) return make_pair(r, c);
            }
        }
        return {-1, -1};  // this should not happen
    }
    
    void generateGraph() {
        Board null_board = {{0, 0, 0}, {0, 0, 0}};
        unordered_set<int> choices = {1, 2, 3, 4, 5, 0};
        vector<Board> boards = generateBoards(null_board, 0, 0, choices);
        
        for (Board b: boards) {
            string repr = getRepr(b);
            board_to_node[repr] = next_node++;
        }   
        
        for (Board b: boards) {
            pair<int, int> crdz = locateZero(b);
            string repr_b = getRepr(b);
            int node_b = board_to_node[repr_b];
            
            vector<pair<int, int>> neighs = {
                {crdz.first-1, crdz.second}, {crdz.first+1, crdz.second}, 
                {crdz.first, crdz.second-1}, {crdz.first, crdz.second+1}
            };
            for (pair<int, int> neigh : neighs) {
                if (neigh.first < 0 || neigh.first >= R || neigh.second < 0 || neigh.second >= C) {continue;}
                Board b2=b;
                std::swap(b2[crdz.first][crdz.second], b2[neigh.first][neigh.second]);
                string repr_b2 = getRepr(b2);
                int node_b2 = board_to_node[repr_b2];                
                adj_list[node_b].insert(node_b2);
                adj_list[node_b2].insert(node_b);
            }
        }                
    }
    
    int bfs() {
        string repr_t = getRepr(target);
        int node_t = board_to_node[repr_t];
        string repr_s = getRepr(source);
        int node_s = board_to_node[repr_s];
        
        // (node, path_len)
        std::queue<pair<int, int>> q;
        std::unordered_set<int> visited;
        q.push({node_s, 0});
        visited.insert(node_s);
        
        while (!q.empty()) {
            auto elem=q.front(); q.pop();
            int node = elem.first;
            int len = elem.second;
            if (node == node_t) {return len;}            
            
            for (int neigh : adj_list[node]) {
                if (visited.find(neigh) != visited.end()) continue;
                visited.insert(neigh);
                q.push({neigh, len+1});
            }
        }
        return -1;  // no path?
    }
    
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        source = board;
        generateGraph();
        int shortest = bfs();
        return shortest;
    }
};
