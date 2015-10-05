// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using std::vector;
using std::priority_queue;
using std::pair;
using std::make_pair;

typedef long long Weight;
typedef pair<Weight, int> SElem; //(wt, yind)

struct Diamond {
    int index;
    int x;
    int y;
    Weight wt;
    Diamond(int i, int xi, int yi, Weight wi) : index(i), x(xi), y(yi), wt(wi) {}
    Diamond& operator=(const Diamond& rhs) {
        index = rhs.index;
        x = rhs.x;
        y = rhs.y;
        wt = rhs.wt;
        return *this;
    }
};

class DLand {
public:
    DLand(int n);
    void solve();
private:
    void readInput();
    void insertSorted(vector<SElem>& scont, int& snelems, SElem elem);

    const int N;
    vector<Diamond> xsort;
    vector<Weight> bestwt;
};

DLand::DLand(int n)
: N(n),
  xsort(N+1, Diamond(0, 0, 0, 0)),
  bestwt(N+1, 0) {

    readInput();

    std::sort(xsort.begin(), xsort.end(), [] (const Diamond& lhs, const Diamond& rhs) -> bool {
        if (lhs.x != rhs.x) {
            return (lhs.x < rhs.x);
        } else {
            return (lhs.y < rhs.y);
        }
    });
}

void DLand::readInput() {

    xsort[0] = Diamond(0, 0, 0, 0); //fictitious diamond of wt 0 at (0, 0)

    for (int i=1; i<=N; i++) {
        int x, y; std::cin >> x >> y;
        Weight w; std::cin >> w;
        xsort[i] = Diamond(i, x, y, w);
    }
}

void DLand::insertSorted(vector<SElem>& scont, int& snelems, SElem elem) {
    scont[snelems++] = elem;
    int ind = snelems - 1;
    while (ind >= 1) {
        if (elem.first > scont[ind-1].first) {
            scont[ind] = elem;
            break;
        }
        scont[ind] = scont[ind-1];
        ind--;
    }
}

void DLand::solve() {
    vector<SElem> scont(N+1, make_pair(0, 0));
    scont[0]= make_pair(0, 0); //fictitious diamond entered here
    int snelems = 1;
    Weight bigmax = 0;

    for (int ind=1; ind<=N; ind++) {
        int yind = xsort[ind].y;

        int sind = snelems-1;
        while (scont[sind].second > yind) {
            sind--;
        }
        bestwt[ind] = scont[sind].first + xsort[ind].wt;

        if (bigmax < bestwt[ind]) {
            bigmax = bestwt[ind];
        }

        SElem elem = make_pair(bestwt[ind], yind);
        insertSorted(scont, snelems, elem);
    }

    std::cout << bigmax << std::endl;
}

int main() {
    int n; std::cin >> n;

    DLand dl(n);
    dl.solve();
}


