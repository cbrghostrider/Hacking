// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

////////////////////////////////////////////////////////////////////////////
//			Union-Find Data Structure
////////////////////////////////////////////////////////////////////////////

class QuickUnion {
public:
    ~QuickUnion() {}
    QuickUnion(const int numKeys);           //adds each key into its own set
    void Union(const int k1, const int k2);  //unions two sets
    int Find(const int k) const;             //finds what set is this key
    int NumSets() const;                     //returns number of sets in DS
private:
    int Root_(int index) const;
    vector<int> arr_;     //each key associated with its set here
    vector<int> sz_;      //size of each tree rooted here
};

QuickUnion::QuickUnion(const int numKeys) 
: arr_(), sz_()
{
    for (int i=0; i<numKeys; i++) {
        arr_.push_back(i);
        sz_.push_back(1); 
    }
}

int QuickUnion::Root_(int index) const
{
    while (index != arr_[index]) {
        index = arr_[index];
    }
    return index;
}

void QuickUnion::Union(const int kf, const int kt)
{
    int from = Root_(kf);
    int to   = Root_(kt);
    if (from == to) return;
    if (sz_[from] < sz_[to]) {
        arr_[from] = to;
        sz_[to] += sz_[from];
    } else {
        arr_[to] = from;
        sz_[from] += sz_[to];
    }
}

int QuickUnion::Find(const int k) const
{
    return Root_(k);
}

int QuickUnion::NumSets() const
{
    vector<int> examine;
    for (int i=0; i<arr_.size(); i++) {
        examine.push_back(Root_(i));
    }
    
    std::sort(examine.begin(), examine.end());
    auto newend = std::unique(examine.begin(), examine.end());
    int ctr=0;
    for (auto it=examine.begin(); it != newend; it++) {
        ctr++;
    }
    return ctr;
}

//////////////////////////////////////////////////////////////////////

enum Status {Empty, Roman, Persian};

class HexWar {
public:
    HexWar(int n, int m);
    void processMoves();
private:
    inline bool romanWin() const;
    inline bool persianWin() const;
    inline int getCoord(int row, int col) const {return (WIDTH*row + col);}
    inline vector<pair<int, int>> getNeighbors(int row, int col) const;

    const int N, M;
    const int WIDTH; //grid top and bottom belong to persians
                     //grid left and right belong to romans
    QuickUnion uf;
    vector<vector<Status>> status;
};

inline bool HexWar::persianWin() const {
    return (uf.Find(getCoord(0, 1)) == uf.Find(getCoord(WIDTH-1, 1)));
}

inline bool HexWar::romanWin() const {
    return (uf.Find(getCoord(1, 0)) == uf.Find(getCoord(1, WIDTH-1)));
}

//will only be called for actual grid, not boundaries
inline vector<pair<int, int>> HexWar::getNeighbors(int row, int col) const {
    vector<pair<int, int>> retval;
    retval.reserve(6);
    retval.emplace_back(make_pair(row-1, col));
    retval.emplace_back(make_pair(row-1, col+1));
    retval.emplace_back(make_pair(row, col-1));
    retval.emplace_back(make_pair(row, col+1));
    retval.emplace_back(make_pair(row+1, col-1));
    retval.emplace_back(make_pair(row+1, col));
    return retval;
}

HexWar::HexWar(int n, int m) 
: N(n), M(m), WIDTH(N+2), 
  uf(WIDTH*WIDTH), 
  status(WIDTH, vector<Status>(WIDTH, Empty)) {

    for (int i=1; i<=N; i++) {
        //connect persian top boundary
        uf.Union(getCoord(0, 1), getCoord(0, i));
        status[0][i] = Persian;

        //connect persian bottom boundary
        uf.Union(getCoord(WIDTH-1, 1), getCoord(WIDTH-1, i));
        status[WIDTH-1][i] = Persian;

        //connect roman left boundary
        uf.Union(getCoord(1, 0), getCoord(i, 0));
        status[i][0] = Roman;

        //connect roman right boundary
        uf.Union(getCoord(1, WIDTH-1), getCoord(i, WIDTH-1));
        status[i][WIDTH-1] = Roman;
    }
}

void HexWar::processMoves() {
    Status stat = Roman; 
    int row, col;

    for (int m=0; m<M; m++) {
        std::cin >> row >> col;
        status[row][col] = stat;

        vector<pair<int, int>> neighbors = getNeighbors(row, col);
        for (const pair<int, int>& neigh : neighbors) {
            int nrow = neigh.first;
            int ncol = neigh.second;
            if (status[nrow][ncol] != stat) continue;

            //if (nrow != 0 && nrow != WIDTH-1 && ncol != 0 && ncol != WIDTH-1) {
            //    std::cout << "Connecting " << "(" << row << "," << col << ")"
            //    << " with (" << nrow << "," << ncol << ")" << std::endl;
            //}
            
            uf.Union(getCoord(row, col), getCoord(nrow, ncol));
        }

        stat = (stat == Roman) ? Persian : Roman;
    }

    if (persianWin()) {
        std::cout << "PERSIANS" << std::endl;
        return;
    }

    if (romanWin()) {
        std::cout << "ROMANS" << std::endl;
        return;
    }

    std::cout << "NEITHER" << std::endl;
}

int main() {
    int n, m; 
    std::cin >> n >> m;

    HexWar hw(n, m);
    hw.processMoves();
}



