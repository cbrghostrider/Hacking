class Solution {
    class Coord {
      public:
        Coord(int xi=0, int yi=0) : x(xi), y(yi) {}
        Coord moveLeft() { x-=1; return *this;}
        Coord moveRight() { x+=1; return *this;}
        Coord moveUp() { y+=1; return *this;}
        Coord moveDown() { y-=1; return *this;}
        uint64_t toHash() {
            uint64_t xneg = (x < 0 ? ((uint64_t)1 << 62) : 0);
            uint64_t yneg = (y < 0 ? ((uint64_t)1 << 63) : 0);
            uint64_t xp = std::abs(x);
            uint64_t yp = std::abs(y);
            return (xneg | yneg | (xp<<20) | yp);
        }
      private:
        int x=0, y=0;
    };
public:
    bool isPathCrossing(string path) {
        unordered_set<uint64_t> coords;
        Coord coord;
        coords.insert(coord.toHash());
        for (char d : path) {
            switch (d) {
                case 'W': coord.moveLeft(); break;
                case 'E': coord.moveRight(); break;
                case 'N': coord.moveUp(); break;
                case 'S': coord.moveDown(); break;
            }
            if (coords.find(coord.toHash()) != coords.end()) return true;
            coords.insert(coord.toHash());
        }
        return false;
    }
};


