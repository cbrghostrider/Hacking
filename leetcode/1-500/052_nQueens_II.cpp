// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    vector<vector<string>> retval;
    
    bool onBoard(vector<string>& bd, int r, int c) {
        return (r >= 0 && r < bd.size() && c >= 0 && c < bd.size());
    }
    
    bool placeQAndMarkUnsafeCells(vector<string>& bd, int row, int col) {
        //mark row and col unsafe
        for(int c=0; c<bd.size(); c++) if (c != col) bd[row][c] = 'U';
        for(int r=0; r<bd.size(); r++) if (r != row) bd[r][col] = 'U';
        
        //mark various diagonals unsafe
        int ri=row-1, ci=col-1;
        while (onBoard(bd, ri, ci)) bd[ri--][ci--] = 'U';
        ri=row-1, ci=col+1;
        while (onBoard(bd, ri, ci)) bd[ri--][ci++] = 'U';
        ri=row+1, ci=col+1;
        while (onBoard(bd, ri, ci)) bd[ri++][ci++] = 'U';    
        ri=row+1, ci=col-1;
        while (onBoard(bd, ri, ci)) bd[ri++][ci--] = 'U';
        
        //place this queen
        bd[row][col] = 'Q';
    }
    
    void convertAndPlaceBoard(vector<string> ret) { //by value on purpose
        for (int r=0; r<ret.size(); r++) {
            for (int c=0; c<ret.size(); c++) {
                if (ret[r][c] == 'U') ret[r][c] = '.';
            }
        }
        retval.push_back(ret);
    }
    
    void placeQueens(vector<string> bd, int num) { //by value on purpose
        if(num == 0) {
            convertAndPlaceBoard(bd);
            return;
        }
        
        vector<string> initBd = bd;
        int row=num-1;
        for (int c=0; c<bd.size(); c++) {
            if (bd[row][c] == '.') {
                placeQAndMarkUnsafeCells(bd, row, c);
                placeQueens(bd, num-1);
                bd = initBd;
            }
        }
    } 
    
public:
    int totalNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        placeQueens(board, n);
        return retval.size();
    }
};
