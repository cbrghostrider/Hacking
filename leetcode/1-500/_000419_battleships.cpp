class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int count=0;
        const int R=board.size();
        const int C=board[0].size();
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (board[r][c] == '.') continue;
                count++;
                
                // Note that the problem conditions make the algorithm below simple.
                
                // check horizontal
                int h_i = c;
                while (h_i < C && board[r][h_i] == 'X') {h_i++;}
                
                // check vertical
                int v_i = r;
                while (v_i < R && board[v_i][c] == 'X') {v_i++;}
                
                if (v_i - r < h_i - c) {
                    for (int i=c; i<h_i; i++) {board[r][i] = '.';}
                } else {
                    for (int i=r; i<v_i; i++) {board[i][c] = '.';}
                }
            }
        }
        return count;
    }
};
