class Solution {
public:
    int perimeterContribution(const vector<vector<int>>& grid, int x, int y) {
        if (grid[y][x] == 0) {
            return 0;
        }
        int con = 0;
        if (x == 0 || grid[y][x-1] == 0) {
            con++;
        }
        if (x == grid[0].size()-1 || grid[y][x+1] == 0) {
            con++;
        }
        if (y == 0 || grid[y-1][x] == 0) {
            con++;
        }
        if (y == grid.size() - 1 || grid[y+1][x] == 0) {
            con++;
        }
        return con;
    }
    
    int islandPerimeter2(vector<vector<int>>& grid) {
        int perimeter = 0;
        for (int y = 0; y < grid.size(); y++) {
            for (int x = 0; x < grid[0].size(); x++) {
                perimeter += perimeterContribution(grid, x, y);
            }
        }
        return perimeter;
    }
    
    /////////////////////////////////////////////////////////////////////////////
    // flood fill using DFS
    /////////////////////////////////////////////////////////////////////////////
    struct Coord {
        int x = -1;
        int y = -1;
    };
    vector<vector<bool>> visited;
    std::vector<Coord> stack;
    int perimeter = 0;
    
    bool isVisited(Coord coord) const {
        return visited[coord.y][coord.x];
    }
    
    void markVisited(Coord coord) {
        visited[coord.y][coord.x] = true;
    }
    
    bool isLand(const vector<vector<int>>& grid, Coord coord) const {
        return grid[coord.y][coord.x] == 1;
    }
    
    bool isWater(const vector<vector<int>>& grid, Coord coord) const {
        return !isLand(grid, coord);
    }
    
    void visit(const vector<vector<int>>& grid, Coord coord) {
        Coord north = {coord.x, coord.y - 1};
        Coord south = {coord.x, coord.y + 1};
        Coord east = {coord.x - 1, coord.y};
        Coord west = {coord.x + 1, coord.y};
        
        if (coord.x == 0 || isWater(grid, east)) {
            perimeter++;
        } else if (!isVisited(east)) {
            markVisited(east);
            stack.push_back(east);
        }
        
        if (coord.x == grid[0].size()-1 || isWater(grid, west)) {
            perimeter++;
        } else if (!isVisited(west)) {
            markVisited(west);
            stack.push_back(west);
        }
        
        if (coord.y == 0 || isWater(grid, north)) {
            perimeter++;
        } else if (!isVisited(north)) {
            markVisited(north);
            stack.push_back(north);
        }
        
        if (coord.y == grid.size()-1 || isWater(grid, south)) {
            perimeter++;
        } else if (!isVisited(south)) {
            markVisited(south);
            stack.push_back(south);
        }
    }
    
    void dfs(const vector<vector<int>>& grid, Coord seed) {
        markVisited(seed);
        stack.push_back(seed);
        
        while (!stack.empty()) {
            Coord coord = stack.back();
            stack.pop_back();
            visit(grid, coord);
        }
    }
    
    int islandPerimeter(vector<vector<int>>& grid) {
        int width = grid[0].size();
        int height = grid.size();
        
        for (int h = 0; h < height; h++) {
            visited.push_back(vector<bool>(width, false));
        }
        
        int seed_x = -1, seed_y = -1;
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                if (grid[h][w] == 1) {
                    seed_x = w;
                    seed_y = h;
                    break;
                }
            }
            if (seed_x != -1) {
                break;
            }
        }
        
        dfs(grid, Coord{seed_x, seed_y});
        return perimeter;
    }
    
};
