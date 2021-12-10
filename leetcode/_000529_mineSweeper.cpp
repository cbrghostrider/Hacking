class Solution {
    int R=0, C=0;
    
    // Processes a single cell.
    // Updates current cell to mine count (or B).
    // Notes which adjacent cells need to be updated.
    // It will mark these cells with a '.' to indicate that they have already been visited
    void processCell(vector<vector<char>>& board, pair<int, int> rc, vector<pair<int, int>>& coords) {
        int mine_count=0;
        int r=rc.first, c=rc.second;
        for (int i=0; i<2; i++) {
            if (r != 0 && c != 0) {  // NW exists
                if (i == 0) { 
                    if (board[r-1][c-1] == 'M' || board[r-1][c-1] == 'X') { mine_count++;}
                } else if (mine_count == 0) {
                    if (board[r-1][c-1] == 'E') {
                        board[r-1][c-1] = '.';
                        coords.push_back({r-1, c-1});
                    }
                }
            }
            if (r != 0 && c != C-1) {  // NE exists
                if (i == 0) { 
                    if (board[r-1][c+1] == 'M' || board[r-1][c+1] == 'X') { mine_count++; }
                } else if (mine_count == 0) {
                    if (board[r-1][c+1] == 'E') {
                        board[r-1][c+1] = '.';
                        coords.push_back({r-1, c+1});
                    }            
                }
            }
            if (r != R-1 && c != 0) {  // SW exists
                if (i == 0) {
                    if (board[r+1][c-1] == 'M' || board[r+1][c-1] == 'X') { mine_count++; }
                } else if (mine_count == 0) {
                    if (board[r+1][c-1] == 'E') {
                        board[r+1][c-1] = '.';
                        coords.push_back({r+1, c-1});
                    } 
                }
            }
            if (r != R-1 && c != C-1) {  // SE exists
                if (i == 0) {
                    if (board[r+1][c+1] == 'M' || board[r+1][c+1] == 'X') {mine_count++;}
                } else if (mine_count == 0) {
                    if (board[r+1][c+1] == 'E') {
                        board[r+1][c+1] = '.';
                        coords.push_back({r+1, c+1});
                    }       
                }
            }
            if (r != 0) {  // N exists
                if (i == 0) {
                    if (board[r-1][c] == 'M' || board[r-1][c] == 'X') {mine_count++;}
                } else if (mine_count == 0) {
                    if (board[r-1][c] == 'E') {
                        board[r-1][c] = '.';
                        coords.push_back({r-1, c});
                    }       
                }
            }
            if (r != R-1) {  // S exists
                if (i == 0) {
                    if (board[r+1][c] == 'M' || board[r+1][c] == 'X') {mine_count++;}
                } else if (mine_count == 0) {
                    if (board[r+1][c] == 'E') {
                        board[r+1][c] = '.';
                        coords.push_back({r+1, c});
                    }       
                }
            }
            if (c != 0) {  // W exists
                if (i == 0) {
                    if (board[r][c-1] == 'M' || board[r][c-1] == 'X') {mine_count++;}
                } else if (mine_count == 0) {
                    if (board[r][c-1] == 'E') {
                        board[r][c-1] = '.';
                        coords.push_back({r, c-1});
                    }       
                }
            }
            if (c != C-1) {  // E exists
                if (i == 0) {
                    if (board[r][c+1] == 'M' || board[r][c+1] == 'X') {mine_count++;}
                } else if (mine_count == 0) {
                    if (board[r][c+1] == 'E') {
                        board[r][c+1] = '.';
                        coords.push_back({r, c+1});
                    }       
                }
            }
        }
        board[r][c] = mine_count == 0 ? 'B' : '0' + mine_count;
    }
    
    
    // Processes an unrevealed blank square at (r, c) recursively.
    void processBoard(vector<vector<char>>& board, int r, int c) {
        std::vector<pair<int, int>> coords;
        coords.push_back({r, c});
        
        while (!coords.empty()) {
            pair<int, int> rc = coords.back();
            coords.pop_back();
            processCell(board, rc, coords);
        }
    }
    
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        R=board.size();
        C=board[0].size();
        const int r=click[0];
        const int c=click[1];
        const char ch = board[r][c];
        
        // out of bounds
        if (r < 0 || r >= R || c < 0 || c >= C) return board;
        
        // clicks on mine (revealed or unrevealed), game over
        if (ch == 'M' || ch == 'X') {
            board[r][c] = 'X';
            return board;
        }
        
        // clicked on an already revealed blank square... why?
        if (ch == 'B' || (ch >= '1' && ch <= '8')) {
            return board;
        }
        
        // process board for an unrevealed blank square
        processBoard(board, r, c);
        return board;
    }
};
