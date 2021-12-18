class Solution {
    class Coord {
        enum Dir {
            NE=0,
            SW=1
        };
        Dir dir=NE;
        int r=0, c=0;
        int R, C;
        int done=0;
        
        // updates r, c for next state
        void prepareNE() {
            if (done == R*C) return;
            
            if (c == C-1) {
                r = r+1;
                dir = SW;
            } else if (r == 0) {
                c = c+1;
                dir = SW;
            } else {
                r -= 1;
                c += 1;
            }
        }
        
        void prepareSW() {
            if (done == R*C) return;
            
            if (r == R-1) {
                c = c+1;
                dir = NE;
            } else if (c == 0) {
                r = r+1;
                dir = NE;
            } else {
                r += 1;
                c -= 1;
            }
        }
        
      public:
        Coord(int total_rows, int total_cols) : R(total_rows), C(total_cols) {}
        
        bool hasNext() { return done < R*C; }    
        
        pair<int, int> next() {
            if (!hasNext()) return {-1, -1};
            pair<int, int> ret = {r, c};
            done++;
            
            // prepare for next
            if (dir == NE) {
                prepareNE();
            } else {
                prepareSW();
            }
            return ret;
        }
    };
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        Coord coord(mat.size(), mat[0].size());
        vector<int> ans;
        while (coord.hasNext()) {
            pair<int, int> rc = coord.next();
            ans.push_back(mat[rc.first][rc.second]);
        }
        return ans;
    }
};
