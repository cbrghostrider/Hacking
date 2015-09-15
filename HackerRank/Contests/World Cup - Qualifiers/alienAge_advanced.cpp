// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <assert.h>
#include <functional>

using std::string;
using std::vector;

typedef int FPrint;

enum Direction {UP=0, DOWN=1, LEFT=2, RIGHT=3};
enum DiagPerpend {NE=0, NW=1, SE=2, SW=3};

//line from right angle intersection to diagonal
struct Cache {
    FPrint fp[4]; //indexed by diagperpend
    Cache() { fp[0] = fp[1] = fp[2] = fp[3] = 0;}
    Cache& operator=(const Cache& rhs) {for (int i=0; i<4; i++) fp[i] = rhs.fp[i]; return (*this);}
};

struct Streak {
    //e.g.how many # upwards, including my position
    FPrint str[4]; //indexed by direction
    Streak() {str[0] = str[1] = str[2] = str[3] = 0;}
};

struct CellData {
    int row;
    int col;
    DiagPerpend dp;
    CellData(int r, int c, DiagPerpend d) : row(r), col(c), dp(d) {}
};

class AlienAge {
public:
    AlienAge(int n, int m);
    int maxAge();
private:
    void readInput();
    void computeStreaks();
    void computeFPSize(int r, int c, int rd, int cd);
    bool onBoard(int r, int c) const {return ((r>=0) && (r<N) && (c>=0) && (c<M));}
    void computeDynProg(DiagPerpend dperp); 
    void computeDynProgAll(); 
    DiagPerpend getDiagPerp(Direction dirx, Direction diry);
    int propagateCoverage(int r, int c, Direction dirx, Direction diry, DiagPerpend dp, const FPrint val, int len); 
    void traverseCells();
    
    const int N, M;
    int occupied;    //number of cells with prints
    vector<vector<bool>>   fprints;
    vector<vector<Cache>>  fpsizes;
    vector<vector<Streak>> streaks;
    vector<vector<FPrint>> coverage;
};

AlienAge::AlienAge(int n, int m)
: N(n), M(m), occupied(0), 
  fprints(N, vector<bool>(M, false)), 
  fpsizes(N, vector<Cache>(M, Cache())), 
  streaks(N, vector<Streak>(M, Streak())),
  coverage(N, vector<FPrint>(M, 0)) {
    readInput();
}

void AlienAge::readInput() {
    string str;
    for (int r=0; r<N; r++) {
        std::cin >> str;
        for (int c=0; c<M; c++) {
            if (str[c] == '#') {
                fprints[r][c] = true;
                occupied++;
            }
        }
    }
}

void AlienAge::computeStreaks() {
    for (int r=0; r<N; r++) {
        int streakLeft = 0;
        for (int c=0; c<M; c++)  {
            if (fprints[r][c]) {
                streakLeft += 1;
            } else {
                streakLeft = 0;
            }
            streaks[r][c].str[LEFT] = streakLeft;
        }
        int streakRight = 0;
        for (int c=M-1; c>=0; c--)  {
            if (fprints[r][c]) {
                streakRight += 1;
            } else {
                streakRight = 0;
            }
            streaks[r][c].str[RIGHT] = streakRight;
        }
    }
    for (int c=0; c<M; c++) {
        int streakTop = 0;
        for (int r=0; r<N; r++) {
            if (fprints[r][c]) {
                streakTop += 1;
            } else {
                streakTop = 0;
            }
            streaks[r][c].str[UP] = streakTop;
        }
        int streakBot = 0;
        for (int r=N-1; r>=0; r--) {
            if (fprints[r][c]) {
                streakBot += 1;
            } else {
                streakBot = 0;
            }
            streaks[r][c].str[DOWN] = streakBot;
        }
    }
}

DiagPerpend AlienAge::getDiagPerp(Direction dirx, Direction diry) {
    assert(dirx == LEFT || dirx == RIGHT);
    assert(diry == UP || diry == DOWN);
    DiagPerpend dp;
    if (diry == UP && dirx == LEFT)    {dp = NW;}
    if (diry == UP && dirx == RIGHT)   {dp = NE;}
    if (diry == DOWN && dirx == LEFT)  {dp = SW;}
    if (diry == DOWN && dirx == RIGHT) {dp = SE;}
    return dp;
}

void AlienAge::computeFPSize(int r, int c, int rdelta, int cdelta) {
    int rdiag = r+rdelta, cdiag = c+cdelta;
    Direction diry = (rdelta < 0) ? UP   : DOWN;
    Direction dirx = (cdelta < 0) ? LEFT : RIGHT;

    DiagPerpend dp = getDiagPerp(dirx, diry);

    FPrint limitx  = streaks[r][c].str[dirx];
    FPrint limity  = streaks[r][c].str[diry];
    FPrint limitxy = std::min(limitx, limity);

    if (!onBoard(rdiag, cdiag) || limitxy <= 2) {
        fpsizes[r][c].fp[dp] = limitxy;
        return;
    }

    FPrint diagsz = fpsizes[rdiag][cdiag].fp[dp];
    fpsizes[r][c].fp[dp] = std::min(limitxy, diagsz+2);
}

void AlienAge::computeDynProg(DiagPerpend dperp) {
    int rbegin, rend, cbegin, cend, rinc, cinc, rdelta, cdelta;
    switch (dperp) {
        case NW : {
            rbegin = 0; cbegin = 0; rend = N-1; cend = M-1; 
            rinc = 1; cinc = 1;
            rdelta = rinc * (-1); cdelta = cinc * (-1);
            break;
        }
        case NE : {
            rbegin = 0; cbegin = M-1; rend = N-1; cend = 0; 
            rinc = 1; cinc = -1;
            rdelta = rinc * (-1); cdelta = cinc * (-1);
            break;
        }
        case SW : {
            rbegin = N-1; cbegin = 0; rend = 0; cend = M-1; 
            rinc = -1; cinc = 1;
            rdelta = rinc * (-1); cdelta = cinc * (-1);
            break;
        }
        case SE : {
            rbegin = N-1; cbegin = M-1; rend = 0; cend = 0; 
            rinc = -1; cinc = -1;
            rdelta = rinc * (-1); cdelta = cinc * (-1);
            break;
        }
    }

    std::function<bool(int, int)> cmple = [] (int lhs, int rhs) -> bool {return (lhs <= rhs);};
    std::function<bool(int, int)> cmpge = [] (int lhs, int rhs) -> bool {return (lhs >= rhs);};

    std::function<bool(int, int)> rfunc = (rinc > 0) ? cmple : cmpge;
    std::function<bool(int, int)> cfunc = (cinc > 0) ? cmple : cmpge;

    for (int ri=rbegin; rfunc(ri, rend); ri += rinc) {
        for (int ci=cbegin; cfunc(ci, cend); ci += cinc) {
            computeFPSize(ri, ci, rdelta, cdelta);
        }
    }
}

void AlienAge::computeDynProgAll() {
    computeDynProg(NE);
    computeDynProg(NW);
    computeDynProg(SE);
    computeDynProg(SW);
}

//returns number of cells written
int AlienAge::propagateCoverage(int r, int c, Direction dirx, Direction diry, DiagPerpend dp, const FPrint val, int len) {
    if (len <= 0) return 0;
    int retval = 0;

    if (diry == UP) {
        for (int ri=r; ri>=r-len+1; ri--) {
            if (coverage[ri][c] < val) {
                coverage[ri][c] = val; //covered by footprint of val size
                retval++;
            }
        }
    } else {
        for (int ri=r; ri<=r+len-1; ri++) {
            if (coverage[ri][c] < val) {
                coverage[ri][c] = val; //covered by footprint of val size
                retval++;
            }
        }
    }

    if (dirx == LEFT) {
        for (int ci=c; ci>=c-len+1; ci--) {
            if (coverage[r][ci] < val) {
                coverage[r][ci] = val; //covered by footprint of val size
                retval++;
            }
        }
    } else {
        for (int ci=c; ci<=c+len-1; ci++) {
            if (coverage[r][ci] < val) {
                coverage[r][ci] = val; //covered by footprint of val size
                retval++;
            }
        }
    }

    int rdiag = r, cdiag = c;
    rdiag += (diry == UP)   ? -1: 1;
    cdiag += (dirx == LEFT) ? -1: 1;

    FPrint dval = onBoard(rdiag, cdiag) ? fpsizes[rdiag][cdiag].fp[dp] : -1;
    if (dval >= val) return retval;

    retval += propagateCoverage(rdiag, cdiag, dirx, diry, dp, val, len-2);
    return retval;
}

void AlienAge::traverseCells() {
    vector<CellData> cds;
    cds.reserve(N*M*4);

    for (int r=0; r<N; r++) {
        for (int c=0; c<M; c++) {
            if (fprints[r][c] == false) continue;
            cds.push_back(CellData(r, c, NW));
            cds.push_back(CellData(r, c, NE));
            cds.push_back(CellData(r, c, SW));
            cds.push_back(CellData(r, c, SE));
        }
    }

    std::sort(cds.begin(), cds.end(), [this] (const CellData& lhs, const CellData& rhs) -> bool {
        return (fpsizes[lhs.row][lhs.col].fp[lhs.dp] > fpsizes[rhs.row][rhs.col].fp[rhs.dp]);
    });

    int processed = 0;
    int cdind = 0;

    //process footprints in a greedy fashion
    while (processed < occupied && cdind < cds.size()) {
        CellData cd = cds[cdind++];
        Direction dirx = (cd.dp == NW || cd.dp == SW) ? LEFT : RIGHT;
        Direction diry = (cd.dp == NE || cd.dp == NW) ? UP : DOWN;
        FPrint val = fpsizes[cd.row][cd.col].fp[cd.dp];
        int written = propagateCoverage(cd.row, cd.col, dirx, diry, cd.dp, val, val);
        processed += written;
    }
}


int AlienAge::maxAge() {
    computeStreaks();
    computeDynProgAll();
    traverseCells();
    FPrint minval = std::numeric_limits<FPrint>::max();
    for (int r=0; r<N; r++) {
        for (int c=0; c<M; c++) {
            if (fprints[r][c] == false) {
                continue;
            }
            if (coverage[r][c] < minval) {
                minval = coverage[r][c];
            }
        }
    }
    return minval;
}


int main() {
    int n, m; std::cin >> n >> m;
    AlienAge aa(n, m);
    int age = aa.maxAge();
    std::cout << age << std::endl;
}

