// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;

typedef long long Elem;
const int MAXN = 500 + 1;
const int MAXM = 500 + 1;
const long long MODNUM = 1000000007;

class Routes {
public:
    Routes();
    long long getRoutes(int n, int m) {return cache[n][m];}
private:
    void computeDPCache();
    vector<vector<Elem>> cache;
};

Routes::Routes() 
: cache(MAXN, vector<Elem>(MAXM, 0)) {
    computeDPCache();
}

void Routes::computeDPCache() {
    cache[0][0] = 1;
    for (int r=0; r<MAXN; r++) {
        for (int c=0; c<MAXM; c++) {
            if (r == 0 && c == 0) continue;
            Elem myroutes = 0;
            if (r != 0) {
                myroutes += cache[r-1][c];
            }
            if (c != 0) {
                myroutes += cache[r][c-1];
            }
            cache[r][c] = myroutes % MODNUM;
        }
    }
}

int main() {
    Routes routes;
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        int n, m; std::cin >> n >> m;
        std::cout << routes.getRoutes(n, m) << std::endl;
    }
}



