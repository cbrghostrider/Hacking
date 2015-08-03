// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Each test is O(1)
//
#include <iostream>
#include <cstdio>
#include <vector>

using std::vector;

class Toilets {
public:
    Toilets(int n, int m);
    void computeIndexAndDirtiness();
private:
    const int N; 
    const int M;
};

Toilets::Toilets(int n, int m)
:N(n), M(m) {
}

void Toilets::computeIndexAndDirtiness() {
    if (N == 1) {   //special case, only 1 toilet
        std::cout << "1 " << (M-1) << std::endl;
        return;
    }

    int index = -1, dirty = -1;

    int m = M - 1; //make 0-indexed
    if ((N%2) == 0){//if N is even
        dirty = ((M-1)/N);
        m %= N;     //it will be like starting over every N people

        if ((m % 2) == 0) {//if new m is even, then he will get a seat from the left
            index = (m/2) + 1; // make 1-indexed
        } else {    //else he will get a seat from the right
            index = N - (m/2);//1-indexed
        }
    } else {        //if N is odd
        m %= (2*N); //every 2*N people, state resets

        if (m < N) {
            dirty = ((M-1) / (2*N) * 2);
            if ((m % 2) == 0) {
                index = (m/2) + 1;
            } else {
                index = N - (m/2);
            }
        } else {
            dirty = ((M-1) / (2*N) * 2) + 1;

            m %= N;
            if ((m % 2) == 0) {
                index = N - (m/2);
            } else {
                index = (m/2) + 1;
            }
        }
    }

    std::cout << index << " " << dirty << std::endl;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        int n, m; std::cin >> n >> m;
        Toilets toilets(n, m);
        toilets.computeIndexAndDirtiness();
    }
}


