// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// note, this version has functional as well as performance issues
// for functionally correct and blazing fast version, see:
// hypercuboid_FINAL.cpp
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;

typedef unsigned long long Ways;

class HyperCube {
private:
    const int nsteps; //the number of steps to be taken
    vector<int> spos; //the starting position in the hypercube
    vector<int> dims; //the dimensions of the hypercube
    Ways *cache[2];   //stores prev and next values of steps over the hypercube

    void allocateCache();
    void freeCache();
    bool onBoard(const vector<int>& index);
    Ways& position(const vector<int>& index, int prevOrNext);
    void writeIndex(const vector<int>& index, Ways value, int prevOrNext);
    Ways readIndex(const vector<int>& index, int prevOrNext); 
    void generateAllIndices(vector<vector<int>>& seed, int curdim);
public:
    HyperCube(int steps, const vector<int>& start, const vector<int>& dims);
    Ways computeWays();
};

HyperCube::HyperCube(int steps, const vector<int>& start, const vector<int>& d)
: nsteps(steps), spos(start), dims(d) {
    cache[0] = cache[1] = NULL;
}

void HyperCube::allocateCache() {
    int cellsNeeded = 1;
    for (const int& d : dims) cellsNeeded *= d;
    cache[0] = new Ways[cellsNeeded];
    cache[1] = new Ways[cellsNeeded];

    //initialize cache, this is base step of recursion
    //at steps=0, I can only go to one place, that is my current place
    vector<vector<int>> allIndices(1, vector<int>());
    generateAllIndices(allIndices, 0);
    for (vector<int>& index : allIndices) {
        writeIndex(index, 1, 0);
        writeIndex(index, 0, 1);
    }
}

void HyperCube::freeCache() {
    delete [] cache[0];
    delete [] cache[1];
}

bool HyperCube::onBoard(const vector<int>& index) {
    for (int i=0; i<dims.size(); i++) {
        if (index[i] < 0 || index[i] >= dims[i]) return false;
    }
    return true;
}

Ways& HyperCube::position(const vector<int>& index, int prevOrNext) {
    assert(onBoard(index) && (prevOrNext == 0 || prevOrNext == 1));
    int chunkSize = 1;              //stores size of current chunk
    Ways* addr = cache[prevOrNext]; //start looking from here
    for (int i = 0; i<dims.size(); i++) chunkSize *= dims[i];  
    for (int i = 0; i<index.size(); i++) {
        chunkSize /= dims[i];                 //adjust my chunkSize
        int newoffset = index[i] * chunkSize; 
        addr += newoffset;                    //adjust ptr
    }
    return *addr;
}

Ways HyperCube::readIndex(const vector<int>& index, int prevOrNext) {
    return position(index, prevOrNext);
}

void HyperCube::writeIndex(const vector<int>& index, Ways value, int prevOrNext) {
    position(index, prevOrNext) = value;
}


void HyperCube::generateAllIndices(vector<vector<int>>& seed, int curdim) {
    if (curdim == dims.size()) return;
    vector<vector<int>> newseed;
    for (int i=0; i<dims[curdim]; i++) {
        vector<vector<int>> oldseed = seed;
        for (vector<int>& seedling : oldseed) {
            seedling.push_back(i);
        }
        newseed.insert(newseed.end(), oldseed.begin(), oldseed.end());
    }
    seed = newseed;
    generateAllIndices(seed, curdim+1);
}

/*
void printAllIndices(vector<vector<int>>& indices) {
    for (vector<int> index : indices) {
        std::cout << "[";
        for (int i=0; i<index.size(); i++) std::cout << index[i] << " ";
        std::cout << "]" << std::endl;
    }
}*/

Ways HyperCube::computeWays() {
    allocateCache();

    vector<vector<int>> allIndices(1, vector<int>());
    generateAllIndices(allIndices, 0);

    //take the required number of steps
    int prev=0, next=1;
    for (int s=0; s<nsteps; s++) {
        for (vector<int>& index : allIndices) {
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
            curWays %= ((Ways) 1000000007);
            writeIndex(index, curWays, next);
        }
        next = 1-next;
        prev = 1-prev;
    }

    Ways ways = readIndex(spos, prev);
    freeCache();
    ways = ways % ((Ways) 1000000007);
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
        HyperCube hc(m, pos, dims);
        Ways ans = hc.computeWays();
        std::cout << ans << std::endl;
    }
}

