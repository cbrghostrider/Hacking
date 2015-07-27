// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using std::vector;

typedef long long Elem;
typedef std::priority_queue<Elem> MaxHeap;

const long long MODNUM = 1000000007;

class CutBoards {
public:
    CutBoards();
    Elem minCost();
private:
    void readInput();
    Elem minCost(int xf, int xt, int yf, int yt);
    int M;
    int N;
    MaxHeap xs; //vertical cuts
    MaxHeap ys; //horizontal cuts
};

CutBoards::CutBoards()
: M(0), N(0), xs(), ys() {
    readInput();
}

void CutBoards::readInput() {
    std::cin >> M >> N;

    for (int i=0; i<M-1; i++) {
        Elem val; std::cin >> val;
        ys.push(val);
    }
    for (int i=0; i<N-1; i++) {
        Elem val; std::cin >> val;
        xs.push(val);
    }
}

Elem CutBoards::minCost() {
    Elem cost = 0;
    long long horizPieces = 1;//pieces made by horizontal cuts (stacked rows)
    long long vertPieces = 1; //pieces made by vertical cuts (stacked columns)
    while (horizPieces < M || vertPieces < N) {
        if (!xs.empty() && (ys.empty() || (xs.top() > ys.top()))) {
            cost += xs.top() * horizPieces;
            vertPieces++;
            xs.pop();
        } else { 
            cost += ys.top() * vertPieces;
            horizPieces++;
            ys.pop();
        }
        cost %= MODNUM;
    }
    return cost;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        CutBoards cb;
        Elem ans = cb.minCost();
        std::cout << ans << std::endl;
    }
}

