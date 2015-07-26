// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

class GridChallenge {
public:
    GridChallenge(int size);
    void evalChallenge();
private:
    void readInput();
    void swapLocations(int row, int col); //this is the only operation permitted in mutating the grid
    void sortRow(int row);  
    vector<vector<char>> grid;
};

GridChallenge::GridChallenge(int size) 
: grid(size, vector<char>(size, '.')) {
    readInput();
}

void GridChallenge::readInput() {
    char ch; 
    for (int r=0; r<grid.size(); r++) {
        for (int c=0; c<grid.size(); c++) {
            std::cin >> ch; 
            grid[r][c] = ch;
        }
    }
}

void GridChallenge::swapLocations(int row, int col) {
    if (row >= grid.size() || col >= grid[row].size() - 1) {
        return;
    }
    std::swap(grid[row][col], grid[row][col+1]);
}

void GridChallenge::sortRow(int row) {
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid.size()-1-i; j++) {
            if (grid[row][j] > grid[row][j+1]) {
                swapLocations(row, j);
            }
        }
    }
}

void GridChallenge::evalChallenge() {
    for (int r=0; r<grid.size(); r++) {
        sortRow(r);
    }
    
    bool possible = true;
    for (int r=1; r<grid.size() && possible; r++) {
        for (int c=0; c<grid.size() && possible; c++) {
            if (grid[r-1][c] > grid[r][c]) {
                possible = false;
            }
        }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
}

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        int sz; std::cin >> sz;
        GridChallenge gc(sz);
        gc.evalChallenge();
    }
}

