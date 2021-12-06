struct Coord {
    int row=0;
    int col=0;
    Coord(int r, int c) : row(r), col(c) {}
    bool operator==(const Coord& rhs) const {
        return (row == rhs.row && col == rhs.col);
    }
};

namespace std {
template <> struct hash<Coord> 
{
  size_t operator()(const Coord& c) const { return ((c.row << 16)|c.col); }
};
}
class Solution {    
    int R=0;
    int C=0;
    
    void growRowWise(const vector<vector<int>>& board, int r, unordered_set<Coord>& out) {
        for (int c=0; c<C; ) {
            if (board[r][c] == 0) {c++; continue;}
            int p = c;
            while (p < C && board[r][p] == board[r][c]) {p++;}
            if (p-c >= 3) {
                for (int i=c; i<p; i++) {out.insert(Coord(r, i));}
            }
            c = p;
        }
    }
    
    void growColWise(const vector<vector<int>>& board, int c, unordered_set<Coord>& out) {
        for (int r=0; r<R; ) {
            if (board[r][c] == 0) {r++; continue;}
            int p = r;
            while (p < R && board[p][c] == board[r][c]) {p++;}
            if (p-r >= 3) {
                for (int i=r; i<p; i++) {out.insert(Coord(i, c));}
            }
            r = p;
        }
    }

    // grow finds which cells needs to be crushed
    void grow(const vector<vector<int>>& board, unordered_set<Coord>& out) {
        for (int r=0; r<R; r++) {growRowWise(board, r, out);}
        for (int c=0; c<C; c++) {growColWise(board, c, out);}
    }
    
    // given a list of cells that need to be crushed, reduce will zero out those cells.
    // it will then collapse cells on top as required
    void reduce(vector<vector<int>>& board, const unordered_set<Coord>& cells) {
        for (Coord c : cells) {
            board[c.row][c.col] = 0;
        }
        for (int c=0; c<C; c++) {
            int copy_to=R-1;
            while (copy_to >= 0) {
                while (copy_to >= 0 && board[copy_to][c] != 0) {copy_to--;}
                if (copy_to < 0) break;
                int copy_from = copy_to;
                while (copy_from >= 0 && board[copy_from][c] == 0) {copy_from--;}
                if (copy_from < 0) break;
                std::swap(board[copy_from][c], board[copy_to][c]);
                copy_to--;
            }
        }
    }
    
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        R = board.size();
        C = board[0].size();
            
        bool change = true;
        while (change) {
            change = false;
            
            unordered_set<Coord> coords;
            grow(board, coords);
            if (!coords.empty()) {
                change = true;
                reduce(board, coords);
            }
        }
        
        return board;
    }
};
