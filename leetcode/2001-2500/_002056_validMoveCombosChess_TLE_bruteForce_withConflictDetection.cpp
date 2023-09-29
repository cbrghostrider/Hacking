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
struct Destination {
    Coord crd;      // the final location desired
    Dir dir;  // the direction to move to get here
};

// Records a conflict for early pruning.
// pieces 1 and 2, moving in directions indicated, conflict at time
// Any combo that has these pieces go beyond is flawed.
struct Conflict {
    int piece1=0;
    Dir dir1;
    int piece2=0;
    Dir dir2;
    int time;
};

class Solution {
    vector<string> pieces;
    vector<vector<int>> init_positions;
    const int R=8;
    const int C=8;
    vector<vector<Destination>> destinations;  // for each index i, the final destinations for piece i
    
    vector<Destination> initial_board;
    
    // early pruning for conflicts
    unordered_map<int, int> conflicts;
    
    int conflictSig(int piece1, int piece2, Dir dir1, Dir dir2) {
        return ((piece1 << 16) | (piece2 << 8) | (dir1 << 4) | (dir2));
    }
    
    void recordConflict(int piece1, int piece2, Dir dir1, Dir dir2, int time) {
        int past=std::numeric_limits<int>::max();
        int sig=conflictSig(piece1, piece2, dir1, dir2);
        
        if (conflicts.find(sig) != conflicts.end()) {
            past = conflicts[sig];
        }
        if (time < past) {
            conflicts[sig] = time;
        }
    }
    
    int timeToMove(int index, Destination dest) {
        Destination start = initial_board[index];
        if (dest.dir == NONE) return 0;
        if (dest.dir == N || dest.dir == NE || dest.dir == NW || 
           dest.dir == S || dest.dir == SE || dest.dir == SW) {
            return std::abs(start.crd.r - dest.crd.r);
        }
        return std::abs(start.crd.c - dest.crd.c);
    }
    
    bool checkConflict(int piece1, int piece2, Destination d1, Destination d2) {
        int sig=conflictSig(piece1, piece2, d1.dir, d2.dir);
        if (conflicts.find(sig) == conflicts.end()) {return false;}
        int t1 = timeToMove(piece1, d1);
        int t2 = timeToMove(piece1, d2);
        int max_t = std::max(t1, t2);
        return (conflicts[sig] <= max_t);
    }
    
    // moves without checking board bounds
    Coord move(Coord crd, Dir dir) {
        int delta_r = 0, delta_c=0;
        if (dir == N || dir == NE || dir == NW) {delta_r = -1;}
        if (dir == S || dir == SE || dir == SW) {delta_r = 1;}
        if (dir == E || dir == NE || dir == SE) {delta_c = -1;}
        if (dir == W || dir == NW || dir == SW) {delta_c = 1;}
        return {crd.r+delta_r, crd.c+delta_c};
    }
    
    void recordMoves(int index, Coord crd, Dir dir) {
        Coord next = move(crd, dir);
        if (next.r < 0 || next.r >= R || next.c < 0 || next.c >= C) return;
        destinations[index].push_back({next, dir});
        recordMoves(index, next, dir);
    }
    
    void genDestination(int i) {
        Coord init = {init_positions[i][0], init_positions[i][1]};
        initial_board.push_back({init, NONE});
        destinations[i].push_back({init, NONE});
        
        if (pieces[i] == "bishop" || pieces[i] == "queen") {
            recordMoves(i, init, NE);
            recordMoves(i, init, NW);
            recordMoves(i, init, SE);
            recordMoves(i, init, SW);
        }
        if (pieces[i] == "rook" || pieces[i] == "queen") {
            recordMoves(i, init, N);
            recordMoves(i, init, S);
            recordMoves(i, init, E);
            recordMoves(i, init, W);            
        }
    }
    
    void genDestinations() {
        destinations = vector<vector<Destination>>(pieces.size(), vector<Destination>());
        for (int i=0; i<pieces.size(); i++) {
            genDestination(i);
        }
    }
    
    // returns whether simulation is successful (conflict free) or not.
    bool simulate(const vector<Destination>& start, const vector<Destination>& end, int cur_time) {
        vector<Destination> next(start.size(), Destination());
        unordered_map<Coord, int> occupied;
        bool keep_going = false;
        for (int i=0; i<start.size(); i++) {
            if (start[i].crd == end[i].crd) {
                next[i] = end[i];
            } else {
                Coord new_crd = move(start[i].crd, start[i].dir);
                next[i] = {new_crd, start[i].dir};
                keep_going = true;
            }
            if (occupied.find(next[i].crd) != occupied.end()) {
                int cwith = occupied[next[i].crd];
                recordConflict(i, cwith, end[i].dir, end[cwith].dir, cur_time+1);
                return false;
            }
            occupied[next[i].crd] = i;
        }
        return keep_going ? simulate(next, end, cur_time+1) : true;
    }
    
public:
    int countCombinations(vector<string>& pcs, vector<vector<int>>& ps) {
        pieces = pcs;
        init_positions = ps;
        for (vector<int>& p_inner : init_positions) {
            for (int& n : p_inner) {
                n -= 1;  // make them all 0-indexed
            } 
        }
        
        genDestinations();
        int total=1;
        for (const auto& d : destinations) {
            total *= d.size();
        }
        
        // pointers into the destinations being tried
        vector<int> cur_ptrs(pieces.size(), 0);  

        auto next = [&cur_ptrs, this]() {            
            for (int i=0; i<cur_ptrs.size(); i++) {
                if (cur_ptrs[i] != destinations[i].size()-1) {
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
            vector<Destination> start = initial_board;
            vector<Destination> end;
            for (int i=0; i<cur_ptrs.size(); i++) {
                end.push_back(destinations[i][cur_ptrs[i]]);
                start[i].dir = end[i].dir;  // override the NONE direction
            }
            
            // check for early exit due to conflicts
            bool early_exit = false;
            for (int i=0; i<end.size(); i++) {
                for (int j=i+1; j<end.size(); j++) {
                    if (checkConflict(i, j, end[i], end[j])) {
                        early_exit = true;
                    }
                }
            }
                        
            if (!early_exit && simulate(start, end, 0)) {count++;}
            total--;
            if (total == 0) break;
            next();            
        }
        return count;
    }
};
