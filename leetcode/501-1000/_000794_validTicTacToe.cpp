class Solution {
    // check if someone has already won
    // check that they did really alternate turns (#x==#o or #x==#o+1)
    
    const int N=3;
    int count_x_total=0;
    int count_o_total=0;
    bool checkAlternate(const vector<string>& board) {
        int count_x=0, count_o=0;
        for (const string& line : board) {
            for (char ch : line) {
                if (ch == 'X') {count_x++;}
                if (ch == 'O') {count_o++;}
            }
        }
        count_x_total = count_x;
        count_o_total = count_o;
        return ((count_x == count_o) || (count_x == count_o+1));
    }
    
    bool checkWinState(const vector<string>& board) {
        int winner_x=0, winner_o=0;
        // rowwise
        for (const string& line : board) {
            if (line == "XXX") {winner_x++;}
            if (line == "OOO") {winner_o++;}
        }
        
        // colwise
        for (int c=0; c<N; c++) {
            int count_x=0, count_o=0;
            for (int r=0; r<N; r++) {
                if (board[r][c] == 'X') count_x++;
                if (board[r][c] == 'O') count_o++;
            }
            if (count_x == N) {winner_x++;};
            if (count_o == N) {winner_o++;};
        }
        
        // diagonal
        {
            int count_x=0, count_o=0;
            for (int r=0, c=0, d=0; d<N; d++) {
                if (board[r+d][c+d] == 'X') { count_x++; }
                if (board[r+d][c+d] == 'O') { count_o++; }                
            }
            if (count_x == N) {winner_x++;};
            if (count_o == N) {winner_o++;};
        }
        
        // anti-diagonal
        {
            int count_x=0, count_o=0;
            for (int r=N-1, c=0, d=0; d<N; d++) {
                if (board[r-d][c+d] == 'X') { count_x++; }
                if (board[r-d][c+d] == 'O') { count_o++; }                
            }
            if (count_x == N) {winner_x++;};
            if (count_o == N) {winner_o++;};
        }
        if (winner_x > 0 && winner_o > 0) return false;
        if (winner_x > 0 && count_x_total == count_o_total) return false;
        if (winner_o > 0 && count_x_total == count_o_total+1) return false;
        return true;
    }
public:
    bool validTicTacToe(vector<string>& board) {
        return (checkAlternate(board) && checkWinState(board));
    }
};
