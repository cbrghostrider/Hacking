// Using a greedy algorithm to grow regions that cannot be captured
class Solution {
    typedef pair<int, int> Coord;
    int nrows;
    int ncols;
    unordered_set<unsigned long> unprocessed;
    unordered_set<unsigned long> processed;
    
    bool exists(Coord crd) {
        return (crd.first >= 0 && crd.first <nrows &&
                crd.second >=0 && crd.second < ncols);
    }
    
    bool crdValid(vector<vector<char>>& board, Coord crd) {
        return (exists(crd) && board[crd.first][crd.second] == 'O' &&
                unprocessed.find(hashCrd(crd)) == unprocessed.end() && 
                processed.find(hashCrd(crd)) == processed.end());
    }
    unsigned long hashCrd(Coord crd) {
        return (((unsigned long)(crd.first) << 32) | ((unsigned long)(crd.second)));
    }
    Coord convCoord(unsigned long val) {
        return (make_pair((int)(val >> 32), (int)((val << 32) >> 32)));
    }
public:
    void solve(vector<vector<char>>& board) {
        if (board.size() == 0 || board[0].size() == 0) return;
        nrows = board.size();
        ncols = board[0].size();

        
        for (int r=0; r<nrows; r++) {
            if (board[r][0] == 'O') unprocessed.insert(hashCrd(make_pair(r, 0)));
            if (ncols > 1 && board[r][ncols-1] == 'O') unprocessed.insert(hashCrd(make_pair(r, ncols-1)));
        }
        for (int c=1; c<ncols-1; c++) { //to avoid corner ones again
            if (board[0][c] == 'O') unprocessed.insert(hashCrd(make_pair(0, c)));
            if (nrows > 1 && board[nrows-1][c] == 'O') unprocessed.insert(hashCrd(make_pair(nrows-1, c)));
        }
        
        while (!unprocessed.empty()) {
            Coord me = convCoord(*(unprocessed.begin()));
            unprocessed.erase(unprocessed.begin());
            
            
            Coord top(me.first-1, me.second);
            Coord bot(me.first+1, me.second);
            Coord left(me.first, me.second-1);
            Coord right(me.first, me.second+1);
            
            if (crdValid(board, top)) unprocessed.insert(hashCrd(top));
            if (crdValid(board, bot)) unprocessed.insert(hashCrd(bot));
            if (crdValid(board, left)) unprocessed.insert(hashCrd(left));
            if (crdValid(board, right)) unprocessed.insert(hashCrd(right));
            
            processed.insert(hashCrd(me));
        }
        
        for (int r=0; r<nrows; r++) {
            for (int c=0; c<ncols; c++) {
                board[r][c] = 'X';
            }
        }
        while (!processed.empty()) {
            Coord me = convCoord(*(processed.begin()));
            processed.erase(processed.begin());
            
            board[me.first][me.second] = 'O';
        }
    }
};

