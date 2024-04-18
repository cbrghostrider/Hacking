class Solution {
enum class Orient {
    HORIZ=0,
    VERT=1
};
struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {
        return r == rhs.r && c == rhs.c;
    }
    bool operator!=(const Coord& rhs) const {
        return !(*this == rhs);
    }
};
struct Info {
    Coord head;
    Coord tail;
    Orient orient;
    int moves=0;
};

int R=0, C=0;

struct explore_hash {
    size_t operator()(const std::pair<Coord, Orient>& in) const {
        size_t oval = (in.second == Orient::HORIZ ? 0 : (((size_t)1) << 32) );
        size_t rval = (((size_t)in.first.r) << 16);
        size_t cval = ((size_t)in.first.c);
        size_t ret = oval | rval | cval;
        return ret;
    }
};

// Hash table to avoid already explored states.
// The key is (tail coord, orientation).
std::unordered_set<std::pair<Coord, Orient>, explore_hash> htable;

bool isExplored(const Coord& tail, Orient orient) {
    explore_hash eh;    
    return (htable.find(make_pair(tail, orient)) != htable.end());
}

void recordExplored(const Coord& tail, Orient orient) {
    explore_hash eh;    
    htable.insert(make_pair(tail, orient));
}

// Predicate functions to check movement.
bool canRotateClockwise(const vector<vector<int>>& grid, const Info& loc) {
    if (loc.orient == Orient::VERT) return false;
    if (loc.head.r == R-1) return false;
    if (grid[loc.tail.r+1][loc.tail.c] == 1) return false;
    if (grid[loc.tail.r+1][loc.tail.c+1] == 1) return false;  // TC 39: requirements should clarify this
    return true;
}
bool canRotateCounterClockwise(const vector<vector<int>>& grid, const Info& loc) {
    if (loc.orient == Orient::HORIZ) return false;
    if (loc.head.c == C-1) return false;
    if (grid[loc.tail.r][loc.tail.c+1] == 1) return false;
    if (grid[loc.tail.r+1][loc.tail.c+1] == 1) return false;  // TC 39: requirements should clarify this
    return true;
}
bool canMoveRight(const vector<vector<int>>& grid, const Info& loc) {
    if (loc.head.c+1 == C) return false;
    if (loc.orient == Orient::VERT) {
        if (grid[loc.head.r][loc.head.c+1] == 1) return false;
        if (grid[loc.tail.r][loc.tail.c+1] == 1) return false;
    } else {  // horizontal        
        if (grid[loc.head.r][loc.head.c+1] == 1) return false;
    }
    return true;
}
bool canMoveDown(const vector<vector<int>>& grid, const Info& loc) {
    if (loc.head.r+1 == R) return false;
    if (loc.orient == Orient::HORIZ) {
        if (grid[loc.head.r+1][loc.head.c] == 1) return false;
        if (grid[loc.tail.r+1][loc.tail.c] == 1) return false;
    } else { // vertical        
        if (grid[loc.head.r+1][loc.head.c] == 1) return false;
    }
    return true;
}

// Movement functions.
// No checks!! Assumes it can do so and is in a valid state.
Info moveClockwise(const Info& loc) {
    Info ret = loc;
    ret.head.r = ret.tail.r+1;
    ret.head.c = ret.tail.c;
    ret.orient = Orient::VERT;
    ret.moves++;    
    return ret;
}
Info moveCounterClockwise(const Info& loc) {
    Info ret = loc;
    ret.head.r = ret.tail.r;
    ret.head.c = ret.tail.c+1;
    ret.orient = Orient::HORIZ;
    ret.moves++;    
    return ret;
}
Info moveRight(const Info& loc) {
    Info ret = loc;
    if (loc.orient == Orient::VERT) {
        ret.tail.c++;
        ret.head.c++;
    } else { // horizontal
        ret.tail = loc.head;
        ret.head.c++;                 
    }
    ret.moves++;   
    return ret;    
}
Info moveDown(const Info& loc) {
    Info ret = loc;
    if (loc.orient == Orient::HORIZ) {
        ret.head.r++;
        ret.tail.r++;
    } else {
        ret.tail = loc.head;
        ret.head.r++;           
    }
    ret.moves++; 
    return ret;    
}

bool isDone(const Info& loc) {
    return loc.head.r == R-1 && loc.tail.r == R-1 && loc.head.c == C-1 && loc.tail.c == C-2;
}

public:
    int minimumMoves(vector<vector<int>>& grid) {
        R=grid.size(); 
        C=grid[0].size();

        Info start = {{0, 1}, {0, 0}, Orient::HORIZ, 0};
        recordExplored(start.tail, start.orient);

        std::queue<Info> q;
        q.push(start);        

        // Simple BFS.
        while (!q.empty()) {
            Info me = q.front(); 
            q.pop();            

            // printf("Checking position: [%d, %d] %s [%d, %d]\n", me.tail.r, me.tail.c, (me.orient == Orient::HORIZ ? ">" : "v"), me.head.r, me.head.c);
            if (isDone(me)) return me.moves;

            if (canRotateClockwise(grid, me)) {
                Info loc = moveClockwise(me);                
                if (!isExplored(loc.tail, loc.orient)) {
                    // printf("[mov=%d] Can CW to T(%d, %d) H(%d, %d)\n", loc.moves, loc.tail.r, loc.tail.c, loc.head.r, loc.head.c);
                    q.push(loc);
                    recordExplored(loc.tail, loc.orient);
                }
            }
            if (canRotateCounterClockwise(grid, me)) {
                Info loc = moveCounterClockwise(me);                
                if (!isExplored(loc.tail, loc.orient)) {
                    // printf("[mov=%d] Can CCW to T(%d, %d) H(%d, %d)\n", loc.moves, loc.tail.r, loc.tail.c, loc.head.r, loc.head.c);
                    q.push(loc);
                    recordExplored(loc.tail, loc.orient);
                }
            }
            if (canMoveRight(grid, me)) {
                Info loc = moveRight(me);                
                if (!isExplored(loc.tail, loc.orient)) {
                    // printf("[mov=%d] Can R to T(%d, %d) H(%d, %d)\n", loc.moves, loc.tail.r, loc.tail.c, loc.head.r, loc.head.c);
                    q.push(loc);
                    recordExplored(loc.tail, loc.orient);
                }
            }
            if (canMoveDown(grid, me)) {
                Info loc = moveDown(me);                
                if (!isExplored(loc.tail, loc.orient)) {
                    // printf("[mov=%d] Can D to T(%d, %d) H(%d, %d)\n", loc.moves, loc.tail.r, loc.tail.c, loc.head.r, loc.head.c);
                    q.push(loc);
                    recordExplored(loc.tail, loc.orient);
                }
            }
        }

        // Pathfinding failed.
        return -1;
    }
};
