// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using std::vector;

typedef unsigned int U32;
typedef unsigned long long NumSeq;

#define MAXELEMS (64)
#define ITERATIONS (8)
#define LIMIT (8000)

//will perform mod after so many iterations
//#define MODCNT (45)  //experimentally determined for U64, dont' touch
#define MODCNT (42)  
//#define MODCNT (15)  //experimentally determined for U32, dont' touch
//#define MODMASK (0x00000003) //to avoid the % for MODCNT testing as much as possible
//#define MODMASK (0x00000001) //to avoid the % for MODCNT testing as much as possible


class Results {
public:
    Results() {
        results = new NumSeq[MAXELEMS];
        //reset();
    }
    inline void reset() {
        std::memset(results, 0, MAXELEMS * sizeof(NumSeq));
    }
    inline Results& operator=(const Results& rhs) {
        std::memcpy(results, rhs.results, MAXELEMS * sizeof(NumSeq));
        return (*this);
    }
    inline NumSeq& operator[] (const size_t index) {
        return results[index];
    }
    inline const NumSeq& operator[] (const size_t index) const {
        return results[index];
    }
    inline void swap(Results& rhs) {
        NumSeq* temp = results;
        results = rhs.results;
        rhs.results = temp;
    }
    ~Results() {
        delete [] results;
    }
private:
    NumSeq* results;
};

class WhiteFalcon {
public:
    WhiteFalcon();
    ~WhiteFalcon();
    void runAlg();
    void printOutput();
private:
    inline void processBufferW(const Results& p, Results& n, U32 asr, U32 bsr);
    inline void reduceMod(Results& c);
    void readInput();
    vector<U32> as;
    vector<U32> bs;
    unsigned int N;
    NumSeq M;

    //the answer needed
    vector<NumSeq> xorCount;
};

WhiteFalcon::WhiteFalcon() 
: as(), bs(), N(0), M(0), xorCount() {
    readInput();

}

WhiteFalcon::~WhiteFalcon() {
}

void WhiteFalcon::readInput() {
    std::cin >> N >> M;
    xorCount = vector<NumSeq>(N+1, 0); //note N+1 for 1-indexing
    as.reserve(N);
    bs.reserve(N);
    for (unsigned int i=0; i<N; i++) {
        U32 num; std::cin >> num;
        as.push_back(num);
    }
    for (unsigned int i=0; i<N; i++) {
        U32 num; std::cin >> num;
        bs.push_back(num);
    }
}
inline void WhiteFalcon::processBufferW(const Results& cachePrev, Results& cacheNext, U32 asr, U32 bsr) {
    cacheNext[0] = cachePrev[asr ^ 0] + cachePrev[bsr ^ 0]; 
    cacheNext[1] = cachePrev[asr ^ 1] + cachePrev[bsr ^ 1]; 
    cacheNext[2] = cachePrev[asr ^ 2] + cachePrev[bsr ^ 2]; 
    cacheNext[3] = cachePrev[asr ^ 3] + cachePrev[bsr ^ 3]; 
    cacheNext[4] = cachePrev[asr ^ 4] + cachePrev[bsr ^ 4]; 
    cacheNext[5] = cachePrev[asr ^ 5] + cachePrev[bsr ^ 5]; 
    cacheNext[6] = cachePrev[asr ^ 6] + cachePrev[bsr ^ 6]; 
    cacheNext[7] = cachePrev[asr ^ 7] + cachePrev[bsr ^ 7]; 
    cacheNext[8] = cachePrev[asr ^ 8] + cachePrev[bsr ^ 8]; 
    cacheNext[9] = cachePrev[asr ^ 9] + cachePrev[bsr ^ 9];
    cacheNext[10] = cachePrev[asr ^ 10] + cachePrev[bsr ^ 10]; 
    cacheNext[11] = cachePrev[asr ^ 11] + cachePrev[bsr ^ 11]; 
    cacheNext[12] = cachePrev[asr ^ 12] + cachePrev[bsr ^ 12]; 
    cacheNext[13] = cachePrev[asr ^ 13] + cachePrev[bsr ^ 13]; 
    cacheNext[14] = cachePrev[asr ^ 14] + cachePrev[bsr ^ 14]; 
    cacheNext[15] = cachePrev[asr ^ 15] + cachePrev[bsr ^ 15]; 
    cacheNext[16] = cachePrev[asr ^ 16] + cachePrev[bsr ^ 16]; 
    cacheNext[17] = cachePrev[asr ^ 17] + cachePrev[bsr ^ 17]; 
    cacheNext[18] = cachePrev[asr ^ 18] + cachePrev[bsr ^ 18]; 
    cacheNext[19] = cachePrev[asr ^ 19] + cachePrev[bsr ^ 19]; 
    cacheNext[20] = cachePrev[asr ^ 20] + cachePrev[bsr ^ 20]; 
    cacheNext[21] = cachePrev[asr ^ 21] + cachePrev[bsr ^ 21]; 
    cacheNext[22] = cachePrev[asr ^ 22] + cachePrev[bsr ^ 22]; 
    cacheNext[23] = cachePrev[asr ^ 23] + cachePrev[bsr ^ 23]; 
    cacheNext[24] = cachePrev[asr ^ 24] + cachePrev[bsr ^ 24]; 
    cacheNext[25] = cachePrev[asr ^ 25] + cachePrev[bsr ^ 25]; 
    cacheNext[26] = cachePrev[asr ^ 26] + cachePrev[bsr ^ 26]; 
    cacheNext[27] = cachePrev[asr ^ 27] + cachePrev[bsr ^ 27]; 
    cacheNext[28] = cachePrev[asr ^ 28] + cachePrev[bsr ^ 28]; 
    cacheNext[29] = cachePrev[asr ^ 29] + cachePrev[bsr ^ 29]; 
    cacheNext[30] = cachePrev[asr ^ 30] + cachePrev[bsr ^ 30]; 
    cacheNext[31] = cachePrev[asr ^ 31] + cachePrev[bsr ^ 31]; 
    cacheNext[32] = cachePrev[asr ^ 32] + cachePrev[bsr ^ 32]; 
    cacheNext[33] = cachePrev[asr ^ 33] + cachePrev[bsr ^ 33]; 
    cacheNext[34] = cachePrev[asr ^ 34] + cachePrev[bsr ^ 34]; 
    cacheNext[35] = cachePrev[asr ^ 35] + cachePrev[bsr ^ 35]; 
    cacheNext[36] = cachePrev[asr ^ 36] + cachePrev[bsr ^ 36]; 
    cacheNext[37] = cachePrev[asr ^ 37] + cachePrev[bsr ^ 37]; 
    cacheNext[38] = cachePrev[asr ^ 38] + cachePrev[bsr ^ 38]; 
    cacheNext[39] = cachePrev[asr ^ 39] + cachePrev[bsr ^ 39]; 
    cacheNext[40] = cachePrev[asr ^ 40] + cachePrev[bsr ^ 40]; 
    cacheNext[41] = cachePrev[asr ^ 41] + cachePrev[bsr ^ 41]; 
    cacheNext[42] = cachePrev[asr ^ 42] + cachePrev[bsr ^ 42]; 
    cacheNext[43] = cachePrev[asr ^ 43] + cachePrev[bsr ^ 43]; 
    cacheNext[44] = cachePrev[asr ^ 44] + cachePrev[bsr ^ 44]; 
    cacheNext[45] = cachePrev[asr ^ 45] + cachePrev[bsr ^ 45]; 
    cacheNext[46] = cachePrev[asr ^ 46] + cachePrev[bsr ^ 46]; 
    cacheNext[47] = cachePrev[asr ^ 47] + cachePrev[bsr ^ 47]; 
    cacheNext[48] = cachePrev[asr ^ 48] + cachePrev[bsr ^ 48]; 
    cacheNext[49] = cachePrev[asr ^ 49] + cachePrev[bsr ^ 49]; 
    cacheNext[50] = cachePrev[asr ^ 50] + cachePrev[bsr ^ 50]; 
    cacheNext[51] = cachePrev[asr ^ 51] + cachePrev[bsr ^ 51]; 
    cacheNext[52] = cachePrev[asr ^ 52] + cachePrev[bsr ^ 52]; 
    cacheNext[53] = cachePrev[asr ^ 53] + cachePrev[bsr ^ 53]; 
    cacheNext[54] = cachePrev[asr ^ 54] + cachePrev[bsr ^ 54]; 
    cacheNext[55] = cachePrev[asr ^ 55] + cachePrev[bsr ^ 55];
    cacheNext[56] = cachePrev[asr ^ 56] + cachePrev[bsr ^ 56]; 
    cacheNext[57] = cachePrev[asr ^ 57] + cachePrev[bsr ^ 57]; 
    cacheNext[58] = cachePrev[asr ^ 58] + cachePrev[bsr ^ 58]; 
    cacheNext[59] = cachePrev[asr ^ 59] + cachePrev[bsr ^ 59]; 
    cacheNext[60] = cachePrev[asr ^ 60] + cachePrev[bsr ^ 60]; 
    cacheNext[61] = cachePrev[asr ^ 61] + cachePrev[bsr ^ 61]; 
    cacheNext[62] = cachePrev[asr ^ 62] + cachePrev[bsr ^ 62]; 
    cacheNext[63] = cachePrev[asr ^ 63] + cachePrev[bsr ^ 63]; 
}

inline void WhiteFalcon::reduceMod(Results& c) {
    c[0] %= M;
    c[1] %= M;
    c[2] %= M;
    c[3] %= M;
    c[4] %= M;
    c[5] %= M;
    c[6] %= M;
    c[7] %= M;
    c[8] %= M;
    c[9] %= M;
    c[10] %= M;
    c[11] %= M;
    c[12] %= M;
    c[13] %= M;
    c[14] %= M;
    c[15] %= M;
    c[16] %= M;
    c[17] %= M;
    c[18] %= M;
    c[19] %= M;
    c[20] %= M;
    c[21] %= M;
    c[22] %= M;
    c[23] %= M;
    c[24] %= M;
    c[25] %= M;
    c[26] %= M;
    c[27] %= M;
    c[28] %= M;
    c[29] %= M;
    c[30] %= M;
    c[31] %= M;
    c[32] %= M;
    c[33] %= M;
    c[34] %= M;
    c[35] %= M;
    c[36] %= M;
    c[37] %= M;
    c[38] %= M;
    c[39] %= M;
    c[40] %= M;
    c[41] %= M;
    c[42] %= M;
    c[43] %= M;
    c[44] %= M;
    c[45] %= M;
    c[46] %= M;
    c[47] %= M;
    c[48] %= M;
    c[49] %= M;
    c[50] %= M;
    c[51] %= M;
    c[52] %= M;
    c[53] %= M;
    c[54] %= M;
    c[55] %= M;
    c[56] %= M;
    c[57] %= M;
    c[58] %= M;
    c[59] %= M;
    c[60] %= M;
    c[61] %= M;
    c[62] %= M;
    c[63] %= M;
}

void WhiteFalcon::runAlg() {
    vector<bool> multCheck(LIMIT, false);//to check modulus quickly
    for (int mult=0; (mult*MODCNT)<LIMIT; mult++) {
        int val  = mult*MODCNT;
        multCheck[val] = true;
    }
    for (int L=0; L<N; L++) {
        Results cachePrev, cacheNext;
        cachePrev.reset();

        cachePrev[as[L]] += 1; //cachePrev[as[L]] %= M;
        cachePrev[bs[L]] += 1; //cachePrev[bs[L]] %= M;

        if (as[L] == 0) { xorCount[1] += 1; /*xorCount[1] %= M;*/ }
        if (bs[L] == 0) { xorCount[1] += 1; /*xorCount[1] %= M;*/ }

        for (int sz=2; sz<=N-L; sz++) {
            int R     = L+sz-1; //current seq I am computing
            U32 asr = as[R];
            U32 bsr = bs[R];

            //use as and bs value here
            processBufferW(cachePrev, cacheNext, asr, bsr);
            
            //if (/*(sz % MODCNT)*/ ((sz & MODMASK) == 0) && ((sz % MODCNT) == 0)) {
            //if (((sz & MODMASK) == 0 ) && ((sz % MODCNT) == 0)) {
            if (multCheck[sz]) {
                reduceMod(cacheNext);
            }
     
            xorCount[sz] += cacheNext[0];
            if (multCheck[L]) xorCount[sz] %= M;

            //prepare for next iteration on this
            cachePrev.swap(cacheNext);
        }
    }
}

void WhiteFalcon::printOutput() {
    for (int i=1; i<=N; i++) {
        std::cout << (xorCount[i] % M) << std::endl;
    }
}

int main () {
    WhiteFalcon wf;
    wf.runAlg();
    wf.printOutput();
}
