/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

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
size_t operator()(const Coord& key) const {
    return ((key.r << 16) | (key.c));
}
};

class Solution {
    unordered_set<Coord> visited;        
    
    // Move robot to align in the desired direction.
    void align(Robot& robot, char cur_dir, char need_dir) {
        if (cur_dir == need_dir) {
            return;
        } else if ((cur_dir == 'U' && need_dir == 'D') || 
            (cur_dir == 'D' && need_dir == 'U') || 
            (cur_dir == 'L' && need_dir == 'R') || 
            (cur_dir == 'R' && need_dir == 'L')) {
            robot.turnRight();
            robot.turnRight();
        } else if ((cur_dir == 'U' && need_dir == 'R') || 
            (cur_dir == 'D' && need_dir == 'L') || 
            (cur_dir == 'L' && need_dir == 'U') || 
            (cur_dir == 'R' && need_dir == 'D')) {
            robot.turnRight();
        } else {
            robot.turnLeft();
        }
    }
    
    char antiDirection(char ch) {
        switch (ch) {
            case 'U': return 'D';
            case 'D': return 'U';
            case 'L': return 'R';
            case 'R': return 'L';
        }
        return ' '; // should not get here...
    }
        
    // Discovers the grid structure using DFS.
    // robot is at cell elem at the start, 
    // and leaves discover routine by returning to cell it came from, 
    // but ends up in that cell in the antiDirection of cur_dir.
    void discover(Robot& robot, Coord elem, char cur_dir) {    
        visited.insert(elem);
        robot.clean();  // clean this coord
        
        vector<pair<char, Coord>> neighs = {
            {'U', {elem.r-1, elem.c}}, {'D', {elem.r+1, elem.c}}, 
            {'L', {elem.r, elem.c-1}}, {'R', {elem.r, elem.c+1}}
        };
        
        for (const auto& neigh : neighs) {
            Coord crd = neigh.second;
            char new_dir = neigh.first;
            if (visited.find(crd) != visited.end()) continue;  // already mapped
                        
            align(robot, cur_dir, new_dir);
            if (robot.move()) {
                discover(robot, crd, new_dir);
                // When the robot moves back after the dfs, it is facing the anti-direction
                align(robot, antiDirection(new_dir), cur_dir);
            } else {
                align(robot, new_dir, cur_dir);
            }       
        }
        
        // send it back to the cell it came from.
        align(robot, cur_dir, antiDirection(cur_dir));
        robot.move();
    }
    
public:
    void cleanRoom(Robot& robot) {
        discover(robot, {201, 201}, 'U');
    }
};
