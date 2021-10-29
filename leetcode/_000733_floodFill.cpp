class Solution {
    struct Coord {
        int x;
        int y;
    };
    vector<vector<bool>> considered;
    vector<Coord> stack;
    int xmax = 0;
    int ymax = 0;
    
    // Note: these methods ignore bounds
    Coord north(Coord c) { return Coord{c.x, c.y - 1}; }
    Coord south(Coord c) { return Coord{c.x, c.y + 1}; }
    Coord west(Coord c) { return Coord{c.x - 1, c.y}; }
    Coord east(Coord c) { return Coord{c.x + 1, c.y}; }
    
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        xmax = image[0].size() - 1;
        ymax = image.size() - 1;
        
        vector<vector<int>> newImage;
        
        for (int i=0; i<image.size(); i++) {
            considered.push_back(vector<bool>(image[0].size(), false));
            newImage.push_back(vector<int>(image[i].begin(), image[i].end()));
        }
        
        const int oldColor = image[sr][sc];
        stack.push_back(Coord{sc, sr});
        considered[sr][sc] = true;
        
        while (!stack.empty()) {
            Coord c = stack.back();
            stack.pop_back();
            newImage[c.y][c.x] = newColor;
            
            if (c.y > 0 && image[c.y-1][c.x] == oldColor && !considered[c.y-1][c.x]) {
                stack.push_back(north(c));
                considered[c.y-1][c.x] = true;
            }
            if (c.y < ymax && image[c.y+1][c.x] == oldColor && !considered[c.y+1][c.x]) {
                stack.push_back(south(c));
                considered[c.y+1][c.x] = true;
            }
            if (c.x > 0 && image[c.y][c.x - 1] == oldColor && !considered[c.y][c.x-1]) {
                stack.push_back(west(c));
                considered[c.y][c.x-1] = true;
            }
            if (c.x < xmax && image[c.y][c.x + 1] == oldColor && !considered[c.y][c.x+1]) {
                stack.push_back(east(c));
                considered[c.y][c.x+1] = true;
            }
        }
        return newImage;
    }
};
