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
    
    // given a starting cell, and a direction, where does the ball end up rolling.
    unordered_map<Coord, unordered_map<Dir, Coord>> rolls;
    
    void computeRolls(const vector<vector<int>>& maze, Coord coord) {
        if (rolls.find(coord) != rolls.end()) return;
        
        Coord temp=coord;
        while (temp.row-1 >= 0 && maze[temp.row-1][temp.col] != 1) {
            temp.row--;
        }
        rolls[coord][N] = temp;
        
        temp=coord;
        while (temp.row+1 < R && maze[temp.row+1][temp.col] != 1) {
            temp.row++;
        }
        rolls[coord][S] = temp;
        
        temp=coord;
        while (temp.col-1 >= 0 && maze[temp.row][temp.col-1] != 1) {
            temp.col--;
        }
        rolls[coord][W] = temp;
        
        temp=coord;
        while (temp.col+1 < C && maze[temp.row][temp.col+1] != 1) {
            temp.col++;
        }
        rolls[coord][E] = temp;
    }
    
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        R=maze.size();
        C=maze[0].size();
        
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        Coord end = {destination[0], destination[1]};
        
        std::queue<Coord> q;
        q.push({start[0], start[1]});
        visited[start[0]][start[1]] = true;
        
        while (!q.empty()) {
            Coord c = q.front();
            q.pop();
            if (c.row == end.row && c.col == end.col) return true;
            
            computeRolls(maze, c);
            vector<Coord> gotoc = {rolls[c][N], rolls[c][S], rolls[c][E], rolls[c][W]};
            
            for (Coord go : gotoc) {
                if (!visited[go.row][go.col]) {
                    q.push({go.row, go.col});
                    visited[go.row][go.col] = true;
                }
            }
        }
        return false;
    }
};
