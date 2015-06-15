// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------

// Functionally correct solution. works for small inputs, but needs more
// algorithmic optimization for large inputs
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;
typedef unsigned int Ways;
#define MODNUM (1000000007)

class HyperCuboid {
private:
    const int nsteps; //the number of steps to be taken
    vector<int> spos; //the starting position in the hypercube
    vector<int> dims; //the dimensions of the hypercube
    Ways *cache[2];   //stores prev and next values of steps over the hypercube

    //cache alloc/dealloc methods
    void allocateCache();
    void freeCache();

    //checking, reading, and writing to indexes
    bool onBoard(const vector<int>& index);
    inline Ways& position(const vector<int>& index, int prevOrNext);
    inline void writeIndex(const vector<int>& index, Ways value, int prevOrNext);
    inline Ways readIndex(const vector<int>& index, int prevOrNext); 

    //iterating over indices
    vector<int> getStartIndex();
    void getNextIndex(vector<int>& index, bool& exists); //simple scheme to iterate on all indices

public:
    HyperCuboid(int steps, const vector<int>& start, const vector<int>& dims);
    Ways computeWays();
};

HyperCuboid::HyperCuboid(int steps, const vector<int>& start, const vector<int>& d)
: nsteps(steps), spos(start), dims(d) {
    cache[0] = cache[1] = NULL;
}

vector<int> HyperCuboid::getStartIndex() {
    return vector<int>(dims.size(), 0);
}

void HyperCuboid::getNextIndex(vector<int>& index, bool& exists) {
    for (int i=dims.size()-1; i>=0; i--) {
        if (index[i] == dims[i] - 1) { //this index reached the end
            index[i] = 0;              //reset it
        } else {
            index[i] += 1;
            break;
        }
    }
    if (index == getStartIndex()) {
        exists = false;
        return;
    }
}

void HyperCuboid::allocateCache() {
    int cellsNeeded = 1;
    for (const int& d : dims) cellsNeeded *= d;
    cache[0] = new Ways[cellsNeeded];
    cache[1] = new Ways[cellsNeeded];

    //initialize cache, this is base step of recursion
    //at steps=0, I can only go to one place, that is my current place
    vector<int> index = getStartIndex();
    bool exists = true;
    while (exists) {
        writeIndex(index, 1, 0);
        writeIndex(index, 0, 1);
        getNextIndex(index, exists);
    }
}

void HyperCuboid::freeCache() {
    delete [] cache[0];
    delete [] cache[1];
}

bool HyperCuboid::onBoard(const vector<int>& index) {
    for (int i=0; i<dims.size(); i++) {
        if (index[i] < 0 || index[i] >= dims[i]) return false;
    }
    return true;
}

Ways& HyperCuboid::position(const vector<int>& index, int prevOrNext) {
    int chunkSize = 1;              //stores size of current chunk
    for (int i = 0; i<dims.size(); i++) chunkSize *= dims[i]; 
    int offset = 0;
    for (int i = 0; i<index.size(); i++) {
        chunkSize /= dims[i];                 //adjust my chunkSize
        offset += index[i] * chunkSize; 
    }
    return cache[prevOrNext][offset];
}

Ways HyperCuboid::readIndex(const vector<int>& index, int prevOrNext) {
    return position(index, prevOrNext);
}

void HyperCuboid::writeIndex(const vector<int>& index, Ways value, int prevOrNext) {
    position(index, prevOrNext) = value;
}

Ways HyperCuboid::computeWays() {
    allocateCache();

    //take the required number of steps
    int prev=0, next=1;
    for (int s=0; s<nsteps; s++) {
        vector<int> index = getStartIndex();
        bool exists = true;
        while (exists) {
            Ways curWays = 0;
            for (int i=0; i<index.size(); i++) {
                vector<int> stepIndexPlus  = index;
                vector<int> stepIndexMinus = index;
                stepIndexPlus[i]  += 1;
                stepIndexMinus[i] -= 1;
                if (onBoard(stepIndexPlus)) {
                    curWays += readIndex(stepIndexPlus, prev);
                }
                if (onBoard(stepIndexMinus)) {
                    curWays += readIndex(stepIndexMinus, prev);
                }
            }
            curWays %= ((Ways) MODNUM);
            writeIndex(index, curWays, next);
            getNextIndex(index, exists);
        }
        next = 1-next;
        prev = 1-prev;
    }

    Ways ways = readIndex(spos, prev);
    freeCache();
    ways = ways % ((Ways) MODNUM);
    return ways;
}

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        int n, m;
        std::cin >> n >> m;
        vector<int> dims, pos;
        for (int i=0; i<n; i++)  {
            int p; std::cin >> p;
            pos.push_back(p-1); //make this 0-indexed right here
        }
        for (int i=0; i<n; i++)  {
            int d; std::cin >> d;
            dims.push_back(d);
        }
        HyperCuboid hc(m, pos, dims);
        Ways ans = hc.computeWays();
        std::cout << ans << std::endl;
    }
}
