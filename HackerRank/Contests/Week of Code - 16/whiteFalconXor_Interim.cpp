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

typedef unsigned char U8;
typedef unsigned long long NumSeq;

#define MAXELEMS (64)

class Results {
public:
    Results() {
        reset();
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
    ~Results() {
    }
private:
    NumSeq results[MAXELEMS];
};

class WhiteFalcon {
public:
    WhiteFalcon();
    ~WhiteFalcon();
    void runDPAlg();
    void printOutput();
private:
    void readInput();
    vector<U8> as;
    vector<U8> bs;
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
        unsigned int num; std::cin >> num;
        as.push_back(num);
    }
    for (unsigned int i=0; i<N; i++) {
        unsigned int num; std::cin >> num;
        bs.push_back(num);
    }
}

//will perform mod after so many iterations
#define MODCNT (40)

void WhiteFalcon::runDPAlg() {

    Results cachePrev, cacheNext;
    int prev=0, next=1;

    for (int L=0; L<N; L++) {
        cachePrev[as[L]] += 1; cachePrev[as[L]] %= M;
        cachePrev[bs[L]] += 1; cachePrev[bs[L]] %= M;

        if (as[L] == 0) { xorCount[1] += 1; xorCount[1] %= M; }
        if (bs[L] == 0) { xorCount[1] += 1; xorCount[1] %= M; }

        for (int sz=2; sz<=N-L; sz++) {
            int R     = L+sz-1; //current seq I am computing

            for (U8 i=0; i<MAXELEMS; i++) {
                NumSeq incBy = cachePrev[i];

                //use as value here
                U8 xorval = i ^ as[R];   //new value created here
                cacheNext[xorval] += incBy; //cacheNext[xorval] %= M;

                //use bs value here
                xorval = i ^ bs[R];   //new value created here
                cacheNext[xorval] += incBy; //cacheNext[xorval] %= M;
            }
            
            if ((sz % MODCNT) == 0) {
                for (U8 i=0; i<MAXELEMS; i++) {
                    cacheNext[i] %= M;
                }
            }
     
            xorCount[sz] += cacheNext[0];
            xorCount[sz] %= M;

            //prepare for next iteration on this
            cachePrev = cacheNext;
            cacheNext.reset();
        }
        cachePrev.reset();
        cacheNext.reset();
    }
}

void WhiteFalcon::printOutput() {
    for (int i=1; i<=N; i++) {
        std::cout << xorCount[i] << std::endl;
    }
}

int main () {
    WhiteFalcon wf;
    wf.runDPAlg();
    wf.printOutput();
}
