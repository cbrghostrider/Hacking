struct Coord {
    int row=0;
    int col=0;
    bool operator<(const Coord& rhs) const {
        if (row != rhs.row) return row < rhs.row;
        return col < rhs.col;
    }
    bool operator==(const Coord& rhs) const {
        return row == rhs.row && col == rhs.col;
    }
};

template<>
struct hash<Coord>
{
std::size_t operator()(const Coord& k) const {
    return ((k.row << 16) | (k.col));
}
};

class Solution {
    
    enum Dir {
        N, S, E, W
    };
    
    int R, C;
    
    struct Info {
        Coord end;
        int dist;
    };
    
    // given a starting cell, and a direction, where does the ball end up rolling.
    // And also how far
    unordered_map<Coord, unordered_map<Dir, Info>> rolls;
    
    void computeRolls(const vector<vector<int>>& maze, Coord coord) {
        if (rolls.find(coord) != rolls.end()) return;
        
        Coord temp=coord;
        while (temp.row-1 >= 0 && maze[temp.row-1][temp.col] != 1) {
            temp.row--;
        }
        rolls[coord][N] = {temp, coord.row - temp.row};
        
        temp=coord;
        while (temp.row+1 < R && maze[temp.row+1][temp.col] != 1) {
            temp.row++;
        }
        rolls[coord][S] = {temp, temp.row - coord.row};
        
        temp=coord;
        while (temp.col-1 >= 0 && maze[temp.row][temp.col-1] != 1) {
            temp.col--;
        }
        rolls[coord][W] = {temp, coord.col - temp.col};
        
        temp=coord;
        while (temp.col+1 < C && maze[temp.row][temp.col+1] != 1) {
            temp.col++;
        }
        rolls[coord][E] = {temp, temp.col - coord.col};
    }
    
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        R=maze.size();
        C=maze[0].size();
        
        vector<vector<int>> visited(R, vector<int>(C, std::numeric_limits<int>::max()));
        Coord end = {destination[0], destination[1]};
        
        std::queue<Info> q;
        q.push({{start[0], start[1]}, 0});
        visited[start[0]][start[1]] = 0;
        int min_dist = std::numeric_limits<int>::max();
        
        while (!q.empty()) {
            auto elem = q.front();
            Coord c = elem.end;
            int dist = elem.dist;
            q.pop();
            if (c.row == end.row && c.col == end.col) {
                if (dist < min_dist) {min_dist = dist;}
                continue;
            }
            
            computeRolls(maze, c);
            vector<Info> gotoi = {rolls[c][N], rolls[c][S], rolls[c][E], rolls[c][W]};
            
            for (Info go : gotoi) {
                if (visited[go.end.row][go.end.col] > go.dist + dist) {
                    q.push({go.end, go.dist + dist});
                    visited[go.end.row][go.end.col] = go.dist + dist;
                }
            }
        }
        return (min_dist == std::numeric_limits<int>::max() ? -1 : min_dist);
    }    
};
