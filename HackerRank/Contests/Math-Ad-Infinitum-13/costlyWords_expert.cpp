// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------

// This code is correct, however it is far slower than what was needed
// In fact I could only clear the sample tests, rest MLE
// As per the editorial, the fast version required knowledge of Stirling numbers (yikes!)
// Including only for completeness

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>

using std::pair;
using std::make_pair;
using std::unordered_map;
using std::vector;

typedef long long Val;
const Val MODNUM = 1000000007;

//////////////////////////////////////////////////////////////////////////////////////

const int PTLIMIT = 7000;

class PascalsTriangle {
private:
    const int N;
    Val** pt;
public:
    PascalsTriangle(int n);
    ~PascalsTriangle();
    Val choose(int n, int k);
};

PascalsTriangle::PascalsTriangle(int n) 
: N(n), pt() { 
    pt = new Val*[n+1];
    for (int i=0; i<=n; i++) {
        pt[i] = new Val[n+1]();
        for (int j=0; j<=n; j++) {
            pt[i][j] = 1;
        }
    }

    for (int row=2; row<=n; row++) {
        for (int col=1; col<row; col++) {
            pt[row][col] = pt[row-1][col-1] + pt[row-1][col];
            pt[row][col] %= MODNUM;
        }
    }
}

PascalsTriangle::~PascalsTriangle() {
    for (int i=0; i<=N; i++) {
        delete [] pt[i];
    }
    delete [] pt;
}

Val PascalsTriangle::choose(int n, int k) {
    if (n <= k || k == 0) return 1;
    return pt[n][k];
}

//////////////////////////////////////////////////////////////////////////////////////

Val myPow(Val x, Val n) {
    if (n == 0) return 1;
    if (n == 1) return x;
    Val subPow = myPow(x, n/2); //divide and conquer
    Val retval = subPow * subPow;
    retval %= MODNUM;
    retval *= (n % 2 == 1 ? x : 1);
    retval %= MODNUM;
    return retval;
}

//////////////////////////////////////////////////////////////////////////////////////

class VallyWords {
public:
    VallyWords(int d);
    void runTestCase();
private:
    Val evalPoly(Val x);
    inline Val makeKey(Val n, Val d);
    Val distinctVal(Val n, Val distinct);
    int D;
    PascalsTriangle pt;
    vector<Val> as;
    unordered_map<Val, Val> polyCache;
    unordered_map<Val, Val> dcostCache;
};

VallyWords::VallyWords(int d)
: D(d), 
  pt(PTLIMIT),
  as(d+1, 0),
  polyCache(),
  dcostCache() {
    for (int i=0; i<=d; i++) {
        std::cin >> as[i];
    }
}

Val VallyWords::evalPoly(Val x) {
    auto it = polyCache.find(x);
    if (it != polyCache.end()) {
        return it->second;
    }

    Val ret = as[0];
    ret %= MODNUM;
    Val xterm = 1;
    for (int ai=1; ai<as.size(); ai++) {
        xterm *= x;
        xterm %= MODNUM;
        Val myterm = xterm * as[ai];
        myterm %= MODNUM;
        ret += myterm;
        ret %= MODNUM;
    }

    polyCache.insert(make_pair(x, ret));
    return ret;
}

inline Val VallyWords::makeKey(Val n, Val d) {
    return ((n << 32) | (d));
}

//fill n positions with exactly d distinct alphabets
Val VallyWords::distinctVal(Val n, Val d) {
    Val key = makeKey(n, d);
    auto it = dcostCache.find(key);
    if (it != dcostCache.end()) {
        return it->second;
    }

    if ((d == 0 && n > 0) || (n == 0 && d > 0) ) { //nothing possible
        Val cost = 0;
        dcostCache.insert(make_pair(key, cost));
        return cost;
    }

    if (n == 0 || d == 1) { //either nothing left to fill, or fill all n positions with same letter (in only 1 possible way)
        Val cost = 1;
        dcostCache.insert(make_pair(key, cost));
        return cost;
    }

    //recursive case
    //choose a letter from the alphabet, and place it in x number of positions
    //now our dist is reduced to (dist-1) and positions reduced to (n-x)
    Val total = 0;
    for (int x=1; x<=n; x++) {
        Val xChoices = pt.choose(n, x);     //choose x positions from n
        Val recursive = distinctVal(n-x, d-1);
        Val term = xChoices * recursive;
        term %= MODNUM;
        total += term;
        total %= MODNUM;
    }

    dcostCache.insert(make_pair(key, total));
    return total;
}

void VallyWords::runTestCase() {
    Val N, M;
    std::cin >> N >> M;

    Val cost=0;
    Val maxdistinct = std::min(N, M);
    for (Val d=1; d<=maxdistinct; d++) {
        Val dcost = evalPoly(d);                 //cost of word having d distinct letters
        Val alphaCost = pt.choose(M, d);         //choosing exactly d letters from alphabet of m
        Val numchoices = distinctVal(N, d);   //number of words of length n having d distinct letters, over alphabet m
        Val term = dcost * numchoices;
        term %= MODNUM;
        term *= alphaCost;
        term %= MODNUM;
        cost += term;
        cost %= MODNUM;
    }
    std::cout << cost << std::endl;
}

int main() {
    int d; std::cin >> d;
    VallyWords cw(d);

    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        cw.runTestCase();
    }
}


