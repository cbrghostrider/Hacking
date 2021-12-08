class Solution {
    unordered_set<long> visited;
    int R, C, max;
    
    long sig(const pair<int, int>& val) {
        return ((long)(val.first) << 32) | ((long)(val.second));
    }
    
    bool isWater(const vector<vector<int>>& grid, const pair<int, int>& cell) {
        if (cell.first < 0 || cell.first >= R) return true;
        if (cell.second < 0 || cell.second >= C) return true;
        return grid[cell.first][cell.second] == 0;
    }
    
    int islandSize(const vector<vector<int>>& grid, int r, int c) {
        int size=0;
        vector<pair<int, int>> todo;
        todo.push_back({r, c});
        visited.insert(sig({r, c}));
        while (!todo.empty()) {
            pair<int, int> rc = todo.back();
            todo.pop_back();
            size++;
            
            pair<int, int> north(rc.first-1, rc.second),   south(rc.first+1, rc.second), 
                           east( rc.first,   rc.second-1), west( rc.first,   rc.second+1);
            if (!isWater(grid, north) && visited.find(sig(north)) == visited.end()) {
                visited.insert(sig(north));
                todo.push_back(north);
            }
            if (!isWater(grid, south) && visited.find(sig(south)) == visited.end()) {
                visited.insert(sig(south));
                todo.push_back(south);
            }
            if (!isWater(grid, east) && visited.find(sig(east)) == visited.end()) {
                visited.insert(sig(east));
                todo.push_back(east);
            }
            if (!isWater(grid, west) && visited.find(sig(west)) == visited.end()) {
                visited.insert(sig(west));
                todo.push_back(west);
            }
        }
        return size;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        max=0;
        R=grid.size();
        C=grid[0].size();
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (visited.find(sig({r, c})) != visited.end() || isWater(grid, {r, c})) { continue; }
                int size = islandSize(grid, r, c);
                if (size > max) {max = size;}
            }
        }
        return max;
    }
};
