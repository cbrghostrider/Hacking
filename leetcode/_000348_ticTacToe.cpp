class TicTacToe {
    int N=0;
    vector<vector<int>> board;
    
    // last move was at (r, c)
    // returns 0, 1, or 2: (in progress, 1 won, 2 won)
    int evaluate(int r, int c, int player) {
        bool won = true;
        for (int i=0; i<N; i++) {
            if (board[r][i] != player) {won = false; break;}
        }
        if (won == true) return player;
        
        won=true;
        for (int i=0; i<N; i++) {
            if (board[i][c] != player) {won = false; break;}
        }
        if (won == true) return player;

        if (r == c) {  // on long diagonal (left top to right bottom)
            won=true;
            for (int d=0, ri=0, ci=0; d<N; d++) {
                if (board[ri+d][ci+d] != player) {won = false; break;}
            }
            if (won == true) return player;
        }
        
        if (r + c == N-1) {
            won=true;
            for (int d=0, ri=N-1, ci=0; d<N; d++) {
                if (board[ri-d][ci+d] != player) {won = false; break;}
            }
            if (won == true) return player;
        }
        
        return 0;
    }
    
public:
    TicTacToe(int n) {
        N=n;
        board = vector<vector<int>>(n, vector<int>(n, 0));
    }
    
    int move(int row, int col, int player) {
        board[row][col] = player;
        return evaluate(row, col, player);
    }
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */
