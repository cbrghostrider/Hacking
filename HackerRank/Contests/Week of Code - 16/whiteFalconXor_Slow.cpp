// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

typedef unsigned char U8;
typedef unsigned int NumSeq;

#define MAXELEMS (64)

struct Results {
    NumSeq* results;
    Results() {
        results = new NumSeq[MAXELEMS];
        for (int i=0; i<MAXELEMS; i++) {
            results[i] = 0;
        }
    }
    ~Results() {
        delete [] results;
    }
};

class WhiteFalcon {
public:
    WhiteFalcon();
    ~WhiteFalcon();
    void runDPAlg();
    void printOutput();
private:
    void readInput();
    void allocCache();
    vector<U8> as;
    vector<U8> bs;
    unsigned int N;
    NumSeq M;

    //the answer needed
    NumSeq* xorCount;
    Results *cache[2];
};

WhiteFalcon::WhiteFalcon() 
: as(), bs(), N(0), M(0), xorCount(), cache() {
    readInput();
    allocCache();
}

void WhiteFalcon::allocCache() {
    cache[0] = new Results[N];
    cache[1] = new Results[N];
    xorCount = new NumSeq[N+1]; //note N+1 for 1-indexing
    for (int i=0; i<N+1; i++) {
        xorCount[i] = 0;
    }
}

WhiteFalcon::~WhiteFalcon() {
    delete [] cache[0];
    delete [] cache[1];
    delete [] xorCount;
}

void WhiteFalcon::readInput() {
    std::cin >> N >> M;
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

void WhiteFalcon::runDPAlg() {

    int prev=0, next=1;

    //base cases for sz=1
    for (int L=0; L<N; L++) {
        int R=L;
        cache[prev][L].results[as[L]] += 1; //one way to xor to as[L] value 
        cache[prev][L].results[as[L]] %= M;
        cache[prev][L].results[bs[L]] += 1; //one way to xor to bs[L] value
        cache[prev][L].results[bs[L]] %= M;

        if (as[L] == 0) {
            xorCount[1] += 1;
            xorCount[1] %= M;
        }
        if (bs[L] == 0) {
            xorCount[1] += 1;
            xorCount[1] %= M;
        }
    }

    for (int sz=2; sz<=N; sz++) {
        for (int L=0; L<=N-sz; L++) {
            int R     = L+sz-1; //current seq I am computing
            //int prevR = R-1;    //seq of 1 less sz

            //use as value here
            for (U8 i=0; i<MAXELEMS; i++) {
                if (cache[prev][L].results[i] == 0) {
                    continue;
                }

                U8 xorval = i ^ as[R];   //new value created here
                NumSeq incBy = cache[prev][L].results[i];
                cache[next][L].results[xorval] += incBy;
                cache[next][L].results[xorval] %= M;

                if (xorval == 0) {
                    //std::cout << "For size " << sz << "[" << L+1 << ", " << R+1 << "] increment by " << incBy << std::endl;
                    xorCount[sz] += incBy;
                    xorCount[sz] %= M;
                }
            }

            //use bs value here
            for (U8 i=0; i<MAXELEMS; i++) {
                if (cache[prev][L].results[i] == 0) {
                    continue;
                }

                U8 xorval = i ^ bs[R];   //new value created here
                NumSeq incBy = cache[prev][L].results[i];
                cache[next][L].results[xorval] += incBy;
                cache[next][L].results[xorval] %= M;

                if (xorval == 0) {
                    //std::cout << "For size " << sz << "[" << L+1 << ", " << R+1 << "] increment by " << incBy << std::endl;
                    xorCount[sz] += incBy;
                    xorCount[sz] %= M;
                }
            }
        }
        for (int L=0; L<N; L++) {
            for (U8 val=0; val<MAXELEMS; val++) {
                cache[prev][L].results[val] = cache[next][L].results[val];
                cache[next][L].results[val] = 0;
            }
        }
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


