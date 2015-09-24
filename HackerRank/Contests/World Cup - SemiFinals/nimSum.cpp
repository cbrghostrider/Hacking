// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <list>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <tuple>

using std::tuple;
using std::get;
using std::make_tuple;
using std::unordered_set;
using std::pair;
using std::make_pair;
using std::list;
using std::vector;

typedef unsigned long long Key;
typedef unsigned int U32;

typedef tuple<U32, U32, U32, int> Result; //(nimsum, leftmost val, rightmost val, size of array)

typedef vector<U32> CONT;

namespace std {
    template <> struct hash<CONT> {
        size_t operator() (const CONT& cont) const {
            size_t hval = 0;
            for (auto val : cont) {
                hval = (hval + (324723947 + val)) ^93485734985;
            }
            return hval;
        }
    };
}

static void printCont(const CONT& cont) {
    for (auto val : cont) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

static inline U32 getNimSum(const Result& res) { return get<0>(res); }
static inline U32 getLHSVal(const Result& res) { return get<1>(res); }
static inline U32 getRHSVal(const Result& res) { return get<2>(res); }
static inline U32 getSize(const Result& res)   { return get<3>(res); }

class NimSum {
public:
    NimSum(int n);
    void winningCombos();
private:
    bool zazaWinGame(const CONT& toks);
    void processArray();
    vector<Result> dncCompute(int lhs, int rhs);

    const int N;
    CONT tokens;
    long long zazawins;

};

NimSum::NimSum(int n)
: N(n), tokens(), zazawins(0) {
    for (int i=0; i<N; i++) {
        U32 val;
        std::cin >> val;
        tokens.push_back(val);
    }
}

bool NimSum::zazaWinGame(const CONT& toks) {
    U32 result = 0;
    for (const U32& val : toks) {
        result ^= val;
    }
    return (result == 0);
}

vector<Result> NimSum::dncCompute(int lhs, int rhs) {
    vector<Result> results;

    if (lhs == rhs) {
        results.push_back(make_tuple(tokens[lhs], tokens[lhs], tokens[lhs], 1));
        return results;
    }

    int mid = (lhs + rhs)/2;
    int midplus = mid + 1;

    vector<Result> lhsres = dncCompute(lhs, mid);
    vector<Result> rhsres = dncCompute(midplus, rhs);

    for (Result l : lhsres) {
        for (Result r : rhsres) {
            //no merging results
            U32 nsim = getNimSum(l) ^ getNimSum(r);
            U32 nlhs = getLHSVal(l);
            U32 nrhs = getRHSVal(r);
            U32 nsize = getSize(l) + getSize(r);
            results.push_back(make_tuple(nsim, nlhs, nrhs, nsize));

            //merging results
            U32 sumval = getRHSVal(l) + getLHSVal(r);
            U32 nmsim = getNimSum(l) ^ getRHSVal(l) ^ getNimSum(r) ^ getLHSVal(r) ^ sumval;
            U32 nmsize = nsize - 1;
            U32 nmlhs, nmrhs;
            if (getSize(l) == 1 && getSize(r) == 1) { //both old chunks sized 1
                nmlhs = nmrhs = sumval;
            } else if (getSize(l) == 1) {
                nmlhs = sumval;
                nmrhs = nrhs;
            } else if (getSize(r) == 1) {
                nmlhs = nlhs;
                nmrhs = sumval;
            } else {
                nmlhs = nlhs;
                nmrhs = nrhs;
            }
            results.push_back(make_tuple(nmsim, nmlhs, nmrhs, nmsize));
        }
    }
  
    return results;
}

void NimSum::processArray() {
    vector<Result> results = dncCompute(0, tokens.size() - 1);
    for (const Result& result : results) {
        if (getNimSum(result) == 0) {
            zazawins++;
        }
    }


}

void NimSum::winningCombos() {
    processArray();
    std::cout << zazawins << std::endl;
}

int main() {
    int n; std::cin >> n;
    NimSum ns(n);
    ns.winningCombos();
}
