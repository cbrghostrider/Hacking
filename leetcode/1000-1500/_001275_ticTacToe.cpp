class Solution {
    vector<vector<char>> board;
    int moves = 0;
    
public:
    // returns 'x', 'o', 't', ' '
    // respectively for X-wins, O-wins, Tie, in-progress
    char calcWinner() {
        for (int r=0; r<3; r++) {
            if (board[r][0] != ' ' && 
                board[r][0] == board[r][1] && board[r][1] == board[r][2]) return board[r][0];
        }
        for (int c=0; c<3; c++) {
            if (board[0][c] != ' ' && 
                board[0][c] == board[1][c] && board[1][c] == board[2][c]) return board[0][c];
        }
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return board[0][0];
        }
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return board[0][2];
        }
        for (int r=0; r<3; r++) {
            for (int c=0; c<3; c++) {
                if (board[r][c] == ' ') return ' ';
            }
        }
        return 't';
    }
    
    string tictactoe(vector<vector<int>>& moves) {
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        char player[2] = {'x', 'o'}; 
        int next = 0;
        for (const vector<int>& move : moves) {
            board[move[0]][move[1]] = player[next];
            next = (next+1)%2;
            char result = calcWinner();
            switch (result) {
                case ' ':
                    continue;
                case 't':
                    return "Draw";
                case 'x':
                    return "A";
                case 'o':
                    return "B";
            }
        }
        return "Pending";
    }
};
