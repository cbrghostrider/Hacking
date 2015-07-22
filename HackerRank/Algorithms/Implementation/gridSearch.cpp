// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

struct Coord {
    int r; 
    int c;
    Coord(int row, int col) : r(row), c(col) {}
};

class GridSearch {
public:
    GridSearch();
    bool findPattern();
private:
    void readInput();
    bool matchAtLocation(Coord coord);
    bool matchLine(Coord coord, int patrow);

    int nrows;
    int ncols;
    vector<string> grid;
    int nrp;
    int ncp;
    vector<string> pattern;
};

GridSearch::GridSearch()
: nrows(0), ncols(0), grid(),
  nrp(0), ncp(0), pattern() {
    readInput();
}

void GridSearch::readInput() {
    std::cin >> nrows >> ncols;
    for (int i=0; i<nrows; i++) {
        string str; std::cin >> str;
        grid.push_back(str);
    }

    std::cin >> nrp >> ncp;
    for (int i=0; i<nrp; i++) {
        string str; std::cin >> str;
        pattern.push_back(str);
    }
}

bool GridSearch::matchLine(Coord onGrid, int patrow) {
    if ((onGrid.c + ncp) > ncols) {
        return false;
    }

    for (int gi=onGrid.c, pi=0; pi<ncp; gi++, pi++) {
        if (grid[onGrid.r][gi] != pattern[patrow][pi]) {
            return false;
        }
    }
    return true;
}

bool GridSearch::matchAtLocation(Coord onGrid) {
    if ((onGrid.r + nrp) > nrows) {
        return false;
    }
    for (int pi=0; pi<nrp; pi++) {
        Coord newcoord = Coord(onGrid.r+pi, onGrid.c);
        if (matchLine(newcoord, pi) == false) {
            return false;
        }
    }
    return true;
}

bool GridSearch::findPattern() {
    for (int gr=0; gr<nrows; gr++) {
        for (int gc=0; gc<ncols; gc++) {
            if (matchAtLocation(Coord(gr, gc))) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        GridSearch gs; 
        bool ans = gs.findPattern();
        std::cout << (ans ? "YES" : "NO") << std::endl;
    }
}

