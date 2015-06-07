// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        const int boardSize = 9;
        const int boxSize   = 3;
        //check row consistency
        for (int rr=0; rr<boardSize; rr++) {
            vector<char> row;
            for (int cc=0; cc<boardSize; cc++) {
                if (board[rr][cc] != '.') row.push_back(board[rr][cc]);
            }
            std::sort(row.begin(), row.end());
            int sizeS = row.size();
            auto it = std::unique(row.begin(), row.end());
            row.erase(it, row.end());
            int sizeU = row.size();
            if (sizeS != sizeU) return false;
        }
        //check col consistency
        for (int cc=0; cc<boardSize; cc++) {
            vector<char> col;
            for (int rr=0; rr<boardSize; rr++) {
                if (board[rr][cc] != '.') col.push_back(board[rr][cc]);
            }
            std::sort(col.begin(), col.end());
            int sizeS = col.size();
            auto it = std::unique(col.begin(), col.end());
            col.erase(it, col.end());
            int sizeU = col.size();
            if (sizeS != sizeU) return false;
        }
        //check box consistency
        for (int rrinit=0; rrinit<boardSize; rrinit += boxSize) {
            for (int ccinit=0; ccinit < boardSize; ccinit += boxSize) {
                vector<char> box;
                for (int rr=rrinit; rr < rrinit+boxSize; rr++) {
                    for (int cc=ccinit; cc<ccinit+boxSize; cc++) {
                        if (board[rr][cc] != '.') box.push_back(board[rr][cc]);
                    }
                }
                std::sort(box.begin(), box.end());
                int sizeS = box.size();
                auto it = std::unique(box.begin(), box.end());
                box.erase(it, box.end());
                int sizeU = box.size();
                if (sizeS != sizeU) return false;
            }
        }
        //everything checked out!
        return true;
    }
};
