class Solution {
    struct Coord {
        int r=0;
        int c=0;
    };
    int R, C;
    vector<vector<int>> mat;

    // Generates all moves possible from given crd.
    vector<Coord> generate(const Coord& crd) {
        vector<Coord> ret;
        vector<Coord> deltas = {
            {1, 2}, {2, 1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {-1, -2}, {-2, -1},
        };
        for (const Coord& delta : deltas) {
            int new_r = crd.r + delta.r;
            int new_c = crd.c + delta.c;
            if (new_r < 0 || new_r >= R || new_c < 0 || new_c >= C) continue;
            if (mat[new_r][new_c]) continue;
            ret.push_back({new_r, new_c});
        }
        return ret;
    }

    bool isDone() {        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (mat[r][c] == 0) return false;
            }
        }
        return true;
    }

    void normalize() {
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                mat[r][c] -= 1;  // convert to 0 based sequence
            }
        }        
    }

    bool traverse(const Coord& crd, int next) {
        vector<Coord> crds = generate(crd);
        mat[crd.r][crd.c] = next;
        if (next == R*C) return true;
        for (const Coord co : crds) { 
            if (mat[co.r][co.c]) continue;           
            if (traverse(co, next+1)) { return true; }
        }
        // Failed!
        mat[crd.r][crd.c] = 0;
        return false;
    }
public:
    vector<vector<int>> tourOfKnight(int m, int n, int r, int c) {
        R=m;
        C=n;
        for (int i=0; i<R; i++) {
            mat.push_back(vector<int>(C, 0));
        }
        if (!traverse({r, c}, 1)) {
            printf("Could not generate traversal!\n");
        }
        normalize();
        return mat;
    }
};
