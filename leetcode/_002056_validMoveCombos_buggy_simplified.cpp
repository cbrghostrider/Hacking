struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {
        return (r == rhs.r && c == rhs.c);
    }
    bool operator<(const Coord& rhs) const {
        if (r != rhs.r) return r < rhs.r;
        return c < rhs.c;
    }
};

template<>
struct hash<Coord> {
size_t operator()(const Coord& crd) const {
    return ((crd.r << 16) | (crd.c));
}
};

enum Dir {
    NONE=0,  // when stationary        
    N, S, E, W, NE, NW, SE, SW        
};

class Solution {
    vector<string> pieces;
    vector<vector<int>> init_positions;
    const int R=8;
    const int C=8;
    
    vector<Coord> initial_board;
    
    int timeToMove(int index, Coord dest, Dir dir) {
        Coord start = initial_board[index];
        if (dir == NONE) return 0;
        if (dir == N || dir == NE || dir == NW || 
           dir == S || dir == SE || dir == SW) {
            return std::abs(start.r - dest.r);
        }
        return std::abs(start.c - dest.c);
    }
    
    // moves without checking board bounds
    Coord move(Coord crd, Dir dir) {        
        if (dir == NONE) return crd;
        
        int delta_r = 0, delta_c=0;
        if (dir == N || dir == NE || dir == NW) {delta_r = -1;}
        if (dir == S || dir == SE || dir == SW) {delta_r = 1;}
        if (dir == E || dir == NE || dir == SE) {delta_c = 1;}
        if (dir == W || dir == NW || dir == SW) {delta_c = -1;}
        return {crd.r+delta_r, crd.c+delta_c};
    }

    vector<Dir> getChoices(string type) {
        vector<Dir> choices;
        choices.push_back(NONE);
        if (type == "bishop" || type == "queen") {
            choices.push_back(NE);
            choices.push_back(NW);
            choices.push_back(SE);
            choices.push_back(SW);
        }
        if (type == "rook" || type == "queen") {
            choices.push_back(N);
            choices.push_back(S);
            choices.push_back(E);
            choices.push_back(W);            
        }        
        return choices;
    }
    
    // returns number of positions for moving in directions.
    int simulate(const vector<Coord>& start, vector<Coord>& last, const vector<Dir>& dirs) {
        bool no_move = true;
        for (Dir d : dirs) {
            if (d != NONE) {no_move = false;}
        }
        if (no_move) return 1;
        
        int count=0;
        bool keep_going=true;
        while (keep_going) {  // until we fall off the board or stop due to conflict...
            vector<Coord> next(start.size(), Coord());
            
            unordered_map<Coord, int> occupied;
            
            for (int i=0; i<start.size(); i++) {
                Coord new_crd = move(last[i], dirs[i]);                
                if (new_crd.r < 0 || new_crd.r >= R || new_crd.c < 0 || new_crd.c >= C) { // fell off board
                    keep_going = false;
                    break;
                }                                
                if (occupied.find(new_crd) != occupied.end()) {  // conflict!                  
                    keep_going = false;
                    break;                    
                }
                
                next[i] = new_crd;
                occupied[next[i]] = i;
            }    
            
            if (!keep_going) {break;}
            
            // reached a valid state, compute combos            
            int none_ctr=0;
            for (int i=0; i<start.size(); i++) {  // i is fixed at new place
                if (dirs[i] == NONE) { none_ctr++; continue ; }
                int prod=1;
                for (int j=0; j<start.size(); j++) {  // j moves across all previous positions
                    if (i == j) continue;
                    int time = timeToMove(j, next[j], dirs[j]) + 1;
                    prod *= time;
                }
                
                count += prod;
            }
            // the max position has been double counted a few times
            int double_count = start.size()-1-none_ctr;
            count -= double_count;
            
            last.clear();
            last.insert(last.end(), next.begin(), next.end());
        }        

        return count;
    }
    
public:
    //
    // This solution has a bug somewhere... probably in the way I count things up above.
    //
    int countCombinations(vector<string>& pcs, vector<vector<int>>& ps) {
        pieces = pcs;
        init_positions = ps;
        for (vector<int>& p_inner : init_positions) {
            for (int& n : p_inner) {
                n -= 1;  // make them all 0-indexed
            } 
        }                
        
        // pointers into the directions being tried
        vector<int> cur_ptrs(pieces.size(), 0);  
        
        vector<vector<Dir>> choices;
        for (int i=0; i<pieces.size(); i++) {
            initial_board.push_back({init_positions[i][0], init_positions[i][1]});
            choices.push_back(getChoices(pieces[i]));            
        }
        
        int total=1;
        for (const auto& d : choices) {
            total *= d.size();
        }
        
        auto next = [&cur_ptrs, &choices]() {            
            for (int i=0; i<cur_ptrs.size(); i++) {
                if (cur_ptrs[i] != choices[i].size()-1) {
                    cur_ptrs[i]++;
                    return;
                } else {
                    cur_ptrs[i] = 0;
                    // continue to next index
                }
            }                            
        };
        
        int count=0;
        while (total != 0) {
            vector<Coord> start = initial_board;
            vector<Coord> last = start;
            vector<Dir> dirs;
            for (int i=0; i<cur_ptrs.size(); i++) {
                dirs.push_back(choices[i][cur_ptrs[i]]);               
            }            
                        
            count += simulate(start, last, dirs);
            total--;
            if (total == 0) break;
            next();            
        }
        return count;
    }
};
