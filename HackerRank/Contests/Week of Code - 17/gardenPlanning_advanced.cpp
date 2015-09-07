// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Unfortunately I could only design an exponential time algorithm
// Using backtracking w/ pruning of the search space as much as possible.
// 11/40 AC, test TLE :-(
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <utility>

using std::pair;
using std::make_pair;
using std::queue;
using std::string;
using std::vector;

typedef long long Ways;
const Ways MODNUM = 1000000007;

struct Coord {
    int row;
    int col;
    Coord(int r, int c) : row(r), col(c) {}
    bool operator==(const Coord& rhs) const {return (row == rhs.row && col == rhs.col);}
    bool operator!=(const Coord& rhs) const {return (!(*this == rhs));}
};
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

////////////////////////////////////////////////////////////////////////////////////
class Garden {
public:
    Garden(int n, int m);
    Ways getWays();
private:
    void countWays();
    void readInput();
    void printGarden();

    bool violationCycle();
    bool violationConnectivity();

    int key(Coord crd) {return (crd.row*M + crd.col);}
    bool inGarden(Coord crd) {return (crd.row >=0 && crd.row < N && crd.col >=0 && crd.col < M);}

    bool visit(vector<vector<bool>>& visited, Coord parent, Coord me, Coord crd);
    bool dfs(vector<vector<bool>>& visited, Coord parent, Coord me); 

    const int N, M;
    vector<string> garden;
    Ways ways;
};

Garden::Garden(int n, int m)
: N(n), M(m), garden(), ways(0) {
    readInput();
}

void Garden::readInput() {
    string str;
    for (int i=0; i<N; i++) {
        std::cin >> str;
        garden.push_back(str);
    }
}

bool Garden::visit(vector<vector<bool>>& visited, Coord parent, Coord me, Coord crd) {
    if (inGarden(crd) && garden[crd.row][crd.col] == '.' && crd != parent) {
        if (dfs(visited, me, crd) == false) return false;
    }
    return true;
}

bool Garden::dfs(vector<vector<bool>>& visited, Coord parent, Coord me) {
    if (visited[me.row][me.col]) return false;
    visited[me.row][me.col] = true;

    Coord up(me.row-1, me.col);
    Coord down(me.row+1, me.col);
    Coord left(me.row, me.col-1);
    Coord right(me.row, me.col+1);

    if (visit(visited, parent, me, up) == false) return false;
    if (visit(visited, parent, me, down) == false) return false;
    if (visit(visited, parent, me, left) == false) return false;
    if (visit(visited, parent, me, right) == false) return false;

    return true;
}

bool Garden::violationCycle() {
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    for (int r=0; r<N; r++) {
        for (int c=0; c<M; c++) {
            if (garden[r][c] != '.') continue;
            if (visited[r][c]) continue;
            if (dfs(visited, Coord(r, c), Coord(r, c)) == false) {
                return true;
            }
        }
    }
    return false;
}

bool Garden::violationConnectivity() {
    Coord point(N, M);

    QuickUnion uf(N*M);
    for (int r=0; r<N; r++) {
        for (int c=0; c<M; c++) {
            if (garden[r][c] == '#') continue; //check both ? and . here

            Coord me(r, c);
            Coord up(r-1, c);
            Coord left(r, c-1);
            if (garden[r][c] == '.') point = me;

            if (inGarden(up) && garden[up.row][up.col] != '#') {
                uf.Union(key(up), key(me));
            }
            if (inGarden(left) && garden[left.row][left.col] != '#') {
                uf.Union(key(left), key(me));
            }
        }
    }

    if (point == Coord(N, M)) {
        return false; //no . connectivity cannot be violated
    }

    int check = uf.Find(key(point));

    for (int r=0; r<N; r++) {
        for (int c=0; c<M; c++) {
            if (garden[r][c] != '.') continue; //important check for . here

            int myRoot = uf.Find(key(Coord(r, c)));
            if (myRoot != check) return true;
        }
    }


    //no violation
    return false;
}

void Garden::printGarden() {
    std::cout << "----------------------------------" << std::endl;
    for (int i=0; i<N; i++) {
        std::cout << garden[i] << std::endl;
    }
    std::cout << "----------------------------------" << std::endl;
}

void Garden::countWays() {
    bool terminal = true;
    int r=0, c=0;
    for (r=0; r<N; r++) {
        for (c=0; c<M; c++) {
            if (!(garden[r][c] == '#' || garden[r][c] == '.') ) {
                terminal = false;
                break;
            }
        }
        if (terminal == false) break;
    }
    if (terminal) {
        //printGarden();
        ways += 1;
        ways %= MODNUM;
        return;
    }
    //put a plot
    {
        garden[r][c] = '.';
        if (!violationCycle() && !violationConnectivity()) {
            countWays();
        }
        garden[r][c] = '?';
    }
    //put a tree
    {
        garden[r][c] = '#';
        if (!violationConnectivity()) {
            countWays();
        }
        garden[r][c] = '?';
    }
}

Ways Garden::getWays() {
    countWays();
    return ways;
}

int main() {
    int n, m; std::cin >> n >> m;

    Garden garden(n, m);
    Ways ans = garden.getWays();
    std::cout << ans << std::endl;
}
