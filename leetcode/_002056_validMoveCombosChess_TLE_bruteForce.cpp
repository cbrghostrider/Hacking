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
class Solution {
    vector<string> pieces;
    vector<vector<int>> init_positions;
    const int R=8;
    const int C=8;
    vector<vector<Destination>> destinations;  // for each index i, the final destinations for piece i
    
    vector<Destination> initial_board;
    
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
    bool simulate(const vector<Destination>& start, const vector<Destination>& end) {
        vector<Destination> next(start.size(), Destination());
        unordered_set<Coord> occupied;
        bool keep_going = false;
        for (int i=0; i<start.size(); i++) {
            if (start[i].crd == end[i].crd) {
                next[i] = end[i];
            } else {
                Coord new_crd = move(start[i].crd, start[i].dir);
                next[i] = {new_crd, start[i].dir};
                keep_going = true;
            }
            if (occupied.find(next[i].crd) != occupied.end()) {return false;}
            occupied.insert(next[i].crd);
        }
        return keep_going ? simulate(next, end) : true;
    }
    
public:
    // Brute force leads to TLE.
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
            
            if (simulate(start, end)) {count++;}
            total--;
            if (total == 0) break;
            next();            
        }
        return count;
    }
};
