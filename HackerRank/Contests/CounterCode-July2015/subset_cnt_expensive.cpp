// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// This version of my solution had cheap add/del, and expensive count
// The other version had expensive add/del, and cheap count
// I gave up after these two solutions
// Turns out the correct answer was to merge these techniques using "meet in the middle" :)
// 
#include <cstdio>
#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

using std::vector;
using std::string;

typedef unsigned int U32;

const int MAXSIZE = (((U32)1) << (16));
const int BITPMAX = 16;

class Subset {
public:
    Subset();
    void runQuery();
private:
    void queryAdd(U32 s);
    void queryDel(U32 s);
    void queryCnt(U32 s);
    vector<int> numCnts;
};

Subset::Subset()
: numCnts(MAXSIZE, 0) {
}

void Subset::runQuery() {
    string str; std::cin >> str;
    U32 num; std::cin >> num;
    if (str == "add") {
        queryAdd(num);
    } else if (str == "del") {
        queryDel(num);
    } else {
        queryCnt(num);
    }
}

void Subset::queryAdd(U32 num) {
    numCnts[num] += 1;
}

void Subset::queryDel(U32 num) {
    numCnts[num] -= 1;
}

void Subset::queryCnt(U32 num) {
    int cnt=0;
    vector<int> indices(1, 0);
    for (int i=0; i<BITPMAX; i++) {
        U32 mask = 0x1 << i;
        if (mask & num) { //add indices
            vector<int> newIndices;
            for (int index : indices) {
                newIndices.push_back(index | mask);
            }
            indices.insert(indices.end(), newIndices.begin(), newIndices.end());
        }
    }
    for (const int index : indices)  {
        cnt += numCnts[index];
    }
    std::cout << cnt << std::endl;
}

int main() {
    int tc; std::cin >> tc; 
    Subset ss;
    for (int i=0; i<tc; i++) {
        ss.runQuery();
    }
}


