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

using namespace std;

// I solved a very similar problem on Leetcode. 
// The solution below is a modified version of my solution on Leetcode.

class QuickUnion {
public:
    ~QuickUnion() {}
    QuickUnion(const int numKeys);           //adds each key into its own set
    void Union(const int k1, const int k2);  //unions two sets
    int Find(const int k) const;             //finds what set is this key
    int NumSets() const;                     //returns number of sets in DS
    int maxSet() const;                      //returns the size of the maximum set in the UF
private:
    int Root_(int index) const;
    vector<int> arr_;     //each key associated with its set here
    vector<int> sz_;      //size of each tree rooted here
};

QuickUnion::QuickUnion(const int numKeys) 
: arr_(), sz_() {
    for (int i=0; i<numKeys; i++) {
        arr_.push_back(i);
        sz_.push_back(1); 
    }
}

int QuickUnion::Root_(int index) const {
    while (index != arr_[index]) {
        index = arr_[index];
    }
    return index;
}

void QuickUnion::Union(const int kf, const int kt) {
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

int QuickUnion::Find(const int k) const {
    return Root_(k);
}

int QuickUnion::NumSets() const {
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

int QuickUnion::maxSet() const {
    int max = 0;
    for (int i=0; i<arr_.size(); i++) {
        if (i == Root_(i)) {
            if (max < sz_[i]) {
                max = sz_[i];
            }
        }
    }
    return max;
}

////////////////////////////////////////////////////////////////////////////
//				main problem
////////////////////////////////////////////////////////////////////////////

class Islands {
    vector<vector<int>> grid;
    void readInput();
public:
    Islands();
    int maxIsland();
};

void Islands::readInput() {
    int m, n;
    std::cin >> m >> n;
    grid = vector<vector<int>>(m, vector<int>(n, 0));
    for (int r=0; r<m; r++) {
        for (int c=0; c<n; c++) {
            int num;
            std::cin >> num;
            grid[r][c] = num;
        }
    }    
}

Islands::Islands() 
: grid() {
    readInput();
}

int Islands::maxIsland() {
    if (grid.size() == 0 || grid[0].size() == 0) {
        return 0;
    }
    
    int ctr=0;
    int crdVals[grid.size()][grid[0].size()]; //assuming perfect mxn grid
    
    for (int v=0; v<grid.size(); v++) {
        for (int h=0; h<grid[v].size(); h++){
            if (grid[v][h] == 1) {
                crdVals[v][h] = ctr++;
            }
        }
    }
    
    QuickUnion uf(ctr);
    
    for (int v=0; v<grid.size(); v++) {
        for (int h=0; h<grid[v].size(); h++) {
            if (v != 0) { //top exists
                if (grid[v-1][h] == 1 && grid[v][h] == 1) {
                    uf.Union(crdVals[v][h], crdVals[v-1][h]);
                }
            }
            if (h != 0) {//left exists
                if (grid[v][h-1] == 1 && grid[v][h] == 1) {
                    uf.Union(crdVals[v][h], crdVals[v][h-1]);
                }
            }
            if (v != 0 && h != 0) { //top-left exists
                if (grid[v-1][h-1] == 1 && grid[v][h] == 1) {
                    uf.Union(crdVals[v][h], crdVals[v-1][h-1]);
                }
            }
            if (v != 0 && h != grid.size()-1) { //top right exists
                if (grid[v-1][h+1] == 1 && grid[v][h] == 1) {
                    uf.Union(crdVals[v][h], crdVals[v-1][h+1]);
                }    
            }
        }
    }
    return uf.maxSet();
}

int main() {
    Islands island;
    int ans = island.maxIsland();
    std::cout << ans << std::endl;
}
