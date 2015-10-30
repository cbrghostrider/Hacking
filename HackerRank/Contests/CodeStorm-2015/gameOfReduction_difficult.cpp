// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using std::unordered_set;
using std::string;
using std::vector;

const int NLIMIT = 6000;

typedef long long Val;

const Val MODNUM = 1000000007;

//////////////////////////////////////////////////////////////////////////////////////////////

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

PascalsTriangle pt(NLIMIT);
//////////////////////////////////////////////////////////////////////////////////////////////

//For this status (of some number), can I reduce it to a terminal [0, 9] in odd or even moves
struct Status {
    bool even;       //can reduce to terminal in exactly even number of moves (direct branch from here)
    bool odd;        //can reduce to terminal in exactly odd number of moves (direct branch from here)
    bool evenOrOdd;  //can reduce to terminal in either even or odd number of moves

    Status() : even(false), odd(false), evenOrOdd(false) {}
    inline Status performMove(); //when one move leads to this result, what is the source of that move
    void printStat() const {
        std::cout << "Odd  = " << (odd ? "True" : "False") ;
        std::cout << " Even = " << (even ? "True" : "False") ;
        std::cout << " E/O  = " << (evenOrOdd ? "True" : "False") ;
        std::cout << std::endl;
    }
};

inline Status Status::performMove() {
    Status ret;
    if (this->even && !this->odd && !this->evenOrOdd) {
        ret.odd = true;
    }
    if (this->odd && !this->even && !this->evenOrOdd) {
        ret.even = true;
    }
    if (this->evenOrOdd) {
        ret.evenOrOdd = true;
    }
    if (this->even && this->odd) {
        ret.evenOrOdd = true;
    }
    return ret;
}

inline Status operator|(const Status& lhs, const Status& rhs) {
    Status ret;
    if (lhs.even && rhs.even) {
        ret.odd = true;
    }
    if (lhs.odd && rhs.odd) {
        ret.even = true;
    }
    if (lhs.evenOrOdd || rhs.evenOrOdd) {
        ret.evenOrOdd = true;
    }
    if ((lhs.even && rhs.odd) || 
        (lhs.odd && rhs.even)) {
        ret.evenOrOdd = true;
    }
    return ret;
}

Status* stats;

inline char combineChar(char x, char y) {
    return ((((x -'0') + (y - '0')) % 10) + '0');
}

Status assignStatus(int n) {
    string nstr = std::to_string(n);
    Status ret;
    bool allodd = true, alleven = true;
    bool anyodd = false, anyeven = false;

    for (int i=1; i<nstr.length(); i++) {
        char mychar = combineChar(nstr[i], nstr[i-1]);
        string remstr = nstr.substr(0, i-1);
        if (mychar != '0' || i != 1 || nstr.length() == 2) remstr += string(1, mychar); 
        if (i != nstr.length() - 1) remstr += nstr.substr(i+1); 
        if (remstr == "") remstr = "0"; 
        int remnum = std::stoi(remstr);
        Status remstat = stats[remnum];
        Status move = remstat.performMove();
        allodd = allodd && move.odd;
        alleven = alleven && move.even;
        anyodd = anyodd || move.odd;
        anyeven = anyeven || move.even;
        ret.evenOrOdd = ret.evenOrOdd || move.evenOrOdd;
    }
    ret.odd = allodd;
    ret.even = alleven;
    if (anyeven && anyodd) ret.evenOrOdd = true; 
    return ret;
}


void initStats() {
    Status init; 
    init.even = true;
    for (int s=0; s<10; s++) {
        stats[s] = init;
    }
    for (int s=10; s<=NLIMIT; s++) {
        stats[s] = assignStatus(s);
    }
}

class Reduction {
public:
    Reduction(int n, int m);
    ~Reduction();
    void playGame();
private:
    void countStat(const Status& stat, int& even, int& odd, int& evenOrOdd); 
    void classifyMissing(int& even, int& odd, int& evenOrOdd);
    Val computeBobCombos(int beven, int bodd, int beo, int aeven, int aodd, int aeo); 
    const int N, M;
    unordered_set<int> ms;
};

Reduction::Reduction(int n, int m) 
: N(n), M(m),
  ms() {
    for (int mi=0; mi<M; mi++) {
        int mval; std::cin >> mval;
        ms.insert(mval);
    }
}

Reduction::~Reduction() {
}

void Reduction::countStat(const Status& stat, int& even, int& odd, int& evenOrOdd) {
    if (stat.even && stat.odd || stat.evenOrOdd) {
        evenOrOdd++;
    } else if (stat.even) {
        even++;
    } else if (stat.odd) {
        odd++;
    }
}

void Reduction::classifyMissing(int& even, int& odd, int& evenOrOdd) {
    even = odd = evenOrOdd = 0;
    for (int i=1; i<=N; i++) {
        if (ms.find(i) != ms.end()) continue;
        const Status& stat = stats[i];
        countStat(stat, even, odd, evenOrOdd);
    }
}

Val Reduction::computeBobCombos(int beven, int bodd, int beo, int aeven, int aodd, int aeo) {
    Val evenCnt=0, oddCnt=0, eoCnt=0;

    //taking any number of even stacks from bob's piles
    for (int k=0; k<=beven; k++) {
        Val val = pt.choose(beven, k);
        evenCnt += val;
        evenCnt %= MODNUM;
    }

    //taking either odd or even number of odd stacks from bob's piles
    //base on how many odd stacks Alice has
    int starto = ((aodd % 2) ? 1 : 0);
    for (int k=starto; k<=bodd; k += 2) {
        Val val = pt.choose(bodd, k);
        oddCnt += val;
        oddCnt %= MODNUM;
    }

    //taking either odd or even number of eo stacks from bob's piles
    //based on how many eo stacks Alice has
    int starteo = ((aeo % 2) ? 1 : 0);
    for (int k=starteo; k<=beo; k += 2) {
        Val val = pt.choose(beo, k);
        eoCnt += val;
        eoCnt %= MODNUM;
    }

    Val tot = evenCnt;
    tot *= oddCnt;
    tot %= MODNUM;
    tot *= eoCnt;
    tot %= MODNUM;

    if (starto == 0 && starteo == 0 ) {
        tot += (MODNUM - 1);
        tot %= MODNUM;
    }
    return tot;
}

void Reduction::playGame() {
    int beven=0, bodd=0, beo=0;
    classifyMissing(beven, bodd, beo);

    int aeven=0, aodd=0, aeo=0;
    for (const int& mnum:ms) {
        const Status& stat = stats[mnum];
        countStat(stat, aeven, aodd, aeo);
    }

    Val ans = computeBobCombos(beven, bodd, beo, aeven, aodd, aeo);

    std::cout << ans << std::endl;
}

int main() {
    stats = new Status[NLIMIT+1];
    initStats();

    int T; std::cin >> T; 
    for (int t=0; t<T; t++) {
        int n, m; std::cin >> n >> m;
        Reduction red(n, m);
        red.playGame();
    }


    delete stats;
}
