// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;

class Boomerang {
public:
    Boomerang(int n);
    void playGame();
private:
    void nextStart(int& start);
    const int N;
    int rems; 
    vector<bool> alive;
};

Boomerang::Boomerang(int n) 
: N(n), rems(n),
  alive(N, true) {
}

void Boomerang::nextStart(int& start) {
    while (alive[start] == false) {
        start = (start + 1) % N;
    }
}

void Boomerang::playGame() {
    int start = 0;
    while (rems > 1) {
        if (rems % 2) { //odd remaining
            alive[start] = false;
            nextStart(start);
            rems--;
        } else {
            int guy = start;

            int cnt = (rems/2);
            while (cnt) {
                if (alive[start]) {
                    cnt--;
                }
                start = (start+1) % N;
            }
            nextStart(start);
            alive[start] = false;
            rems--;

            if (rems > 1) {
                guy = (guy+1) % N;
                nextStart(guy);
                start = guy;
            } else {
                start = guy;
            }
        }
    }
    std::cout << (start + 1) << std::endl;
}

int main() {
    int T; std::cin >> T;
    for (int t=0; t<T; t++) {
        int n; std::cin >> n;
        Boomerang b(n);
        b.playGame();
    }
}

