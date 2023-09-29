// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    typedef pair<int, int> Coord;
    
    bool onBoard(Coord coord, int dimr, int dimc) {
        return (coord.first >=0 && coord.first <dimr && coord.second>=0 && coord.second<dimc);
    }
    
    bool traverse(vector<vector<char>>& board, vector<vector<bool>>& grid, Coord coord, string word, int index) {
        if (index >= word.length()) return true;
        vector<Coord> neighbors = {make_pair(coord.first-1, coord.second), make_pair(coord.first+1, coord.second), 
                                   make_pair(coord.first, coord.second-1), make_pair(coord.first, coord.second+1)};
        for (Coord& nb : neighbors) {
            if (!onBoard(nb, board.size(), board[0].size()) || grid[nb.first][nb.second] == true || 
                 board[nb.first][nb.second] != word[index]) continue;
            grid[nb.first][nb.second] = true;
            if (traverse(board, grid, nb, word, index+1)) return true;
            grid[nb.first][nb.second] = false;
        }
        return false;
    }
    
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.size() == 0 || board[0].size() == 0 || word.length() == 0) return false;
        
        vector<vector<bool>> grid;
        for (int i=0; i<board.size(); i++) grid.push_back(vector<bool>(board[0].size(), false)); 
        
        for (int r=0; r<board.size(); r++) {
            for (int c=0; c<board[0].size(); c++) {
                if (board[r][c] == word[0]) {
                    grid[r][c] = true;
                    if (traverse(board, grid, make_pair(r, c), word, 1)) return true;
                    grid[r][c] = false;
                }
            }
        }
        return false;
    }
};
