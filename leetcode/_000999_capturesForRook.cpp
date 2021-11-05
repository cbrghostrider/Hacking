class Solution {
public:
    int captureInDir(const vector<vector<char>>& board, int rook_r, int rook_c, int delta_r, int delta_c) {
        while (rook_r >=0 && rook_r < board.size() && 
               rook_c >=0 && rook_c < board[0].size()) {
            switch (board[rook_r][rook_c]) {
                case 'R':
                case '.':
                    break;
                case 'B':
                    return 0;
                case 'p':
                    return 1;
                default:
                    break;
                    // Should not happen.
            }
            rook_r += delta_r;
            rook_c += delta_c;
        }
        return 0;
    }
    
    int numRookCaptures(vector<vector<char>>& board) {
        int rook_r = -1, rook_c = -1;
        for (int r=0; r<board.size(); r++) {
            for (int c=0; c<board[0].size(); c++) {
                if (board[r][c] == 'R') {
                    rook_r = r;
                    rook_c = c;
                    break;
                }
            }
        }
        int ans = captureInDir(board, rook_r, rook_c, -1,  0) +
                  captureInDir(board, rook_r, rook_c,  1,  0) +
                  captureInDir(board, rook_r, rook_c,  0, -1) + 
                  captureInDir(board, rook_r, rook_c,  0,  1);
        return ans;
    }
};
