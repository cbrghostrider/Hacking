// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>

using std::vector;

#define MODNUM (1000000007)

typedef unsigned long Elem;
/////////////////////////////////////////////////////////////////////////////////////////

// pascal's triangle to compute (n `choose` k) ; use dynamic programming for this as well!!
// PROGRAMMER BEWARE!! n choose k will overflow for example for 300 choose 150
// therefore I am only storing a modified pascals' triangle, where each value is mod MODNUM
class PascalsTriangle {
private:
    vector<vector<unsigned long long>> pt;
public:
    PascalsTriangle(int n);
    unsigned long long choose(int n, int k);
};

PascalsTriangle::PascalsTriangle(int n) 
: pt(vector<vector<unsigned long long>>(n+1, vector<unsigned long long>(n+1, 1))) { //init [n+1][n+1] matrix to 1s
    for (int row=2; row<=n; row++) {
        for (int col=1; col<row; col++) {
            pt[row][col] = pt[row-1][col-1] + pt[row-1][col];
            pt[row][col] %= (unsigned long long) MODNUM;
        }
    }
}

unsigned long long PascalsTriangle::choose(int n, int k) {
    if (n <= k || k == 0) return 1;
    return pt[n][k];
}

static Elem myPow(Elem x, Elem p) {
  if (p == 0) return 1;
  if (p == 1) return x;
  return ((x * myPow(x, p-1)) % MODNUM);
}

/////////////////////////////////////////////////////////////////////////////////////////

class LuckyNumbers {
public:
    LuckyNumbers(unsigned int x, unsigned int y, unsigned int z);
    ~LuckyNumbers();
    Elem computeResult();
private:
    void allocCache();
    unsigned int nx, ny, nz;
    Elem ***cache;
    PascalsTriangle pt;
};

LuckyNumbers::LuckyNumbers(unsigned int x, unsigned int y, unsigned int z)
: nx(x), ny(y), nz(z), cache(nullptr), pt(x+y+z) {
    allocCache();
}

void LuckyNumbers::allocCache() {
    cache = new Elem**[nx+1];
    for (int i=0; i<=nx; i++) {
        cache[i] = new Elem*[ny+1];
    }
    for (int i=0; i<=nx; i++) {
        for (int j=0; j<=ny; j++) {
            cache[i][j] = new Elem[nz+1];
        }
    }
    for (int i=0; i<=nx; i++) {
        for (int j=0; j<=ny; j++) {
            for (int k=0; k<=nz; k++) {
                cache[i][j][k] = 0;
            }
        }
    }
}

LuckyNumbers::~LuckyNumbers() {
    for (int i=0; i<=nx; i++) {
        for (int j=0; j<=ny; j++) {
            delete [] cache[i][j];
        }
    }
    for (int i=0; i<=nx; i++) {
        delete [] cache[i];
    }
    delete [] cache;
}

Elem LuckyNumbers::computeResult() {
    //dp alg
    for (unsigned int x=0; x<=nx; x++) {         //number of 4s
        for (unsigned int y=0; y<=ny; y++) {     //number of 5s
            for (unsigned int z=0; z<=nz; z++) { //number of 6s
                Elem numDigs = (x+y+z) - 1; 
                if ((x + y + z) == 0) continue; 
                Elem multiplier = myPow(10, numDigs);
                Elem elem=0;
                if (x != 0) {
                    Elem combos = pt.choose(numDigs, x-1) * pt.choose(y+z, y);
                    combos %= MODNUM;
                    Elem thisval = multiplier * 4 * combos + cache[x-1][y][z];
                    thisval %= MODNUM;
                    elem += thisval;
                    elem %= MODNUM;
                }
                if (y != 0) {
                    Elem combos = pt.choose(numDigs, y-1) * pt.choose(x+z, x);
                    combos %= MODNUM;
                    Elem thisval = multiplier * 5 * combos + cache[x][y-1][z];
                    thisval %= MODNUM;
                    elem += thisval;
                    elem %= MODNUM;
                }
                if (z != 0) {
                    Elem combos = pt.choose(numDigs, z-1) * pt.choose(x+y, x);
                    combos %= MODNUM;
                    Elem thisval = multiplier * 6 * combos + cache[x][y][z-1];
                    thisval %= MODNUM;
                    elem += thisval;
                    elem %= MODNUM;
                }
                cache[x][y][z] = elem;
            }
        }
    }

    Elem sum = 0;
    for (int i=0; i<=nx; i++) {
        for (int j=0; j<=ny; j++) {
            for (int k=0; k<=nz; k++) {
                sum += cache[i][j][k];
                sum %= MODNUM;
            }
        }
    }
    return sum;
}

int main() {
    unsigned int x, y, z;
    std::cin >> x >> y >> z;
    LuckyNumbers ln(x, y, z);
    Elem ans = ln.computeResult();
    std::cout << ans << std::endl;
}


