// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// O(n^2*m^2) time and O(nm) space yikes! Passes all test cases though
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

class Fence {
public:
    Fence(int m, int n);
    int computePerimeter();
private:
    void readInput();
    void preprocess();
    int M;
    int N;
    vector<vector<char>> land;
    vector<vector<int>> streakLeft;
    vector<vector<int>> streakUp;
};

Fence::Fence(int m, int n) 
: M(m), N(n), land(), streakLeft(), streakUp() {
    readInput();
}

void Fence::readInput() {
    land = vector<vector<char>>(M, vector<char>());
    
    for (int mi = 0; mi < M; mi++) {
        for (int ni=0; ni < N; ni++) {
            char c; std::cin >> c;
            land[mi].push_back(c);
        }
    }
}

void Fence::preprocess() {
    streakLeft = vector<vector<int>>(M, vector<int>(N, 0));
    streakUp   = vector<vector<int>>(M, vector<int>(N, 0));
    
    for (int i=0; i<M; i++) {
        int streak = 0;
        for (int j=0; j<N; j++) {
            if (land[i][j] == '.') {
                streak++;
            } else {
                streak = 0;
            }
            streakLeft[i][j] = streak;
        }
    }
    for (int i=0; i<N; i++) {
        int streak = 0;
        for (int j=0; j<M; j++) {
            if (land[j][i] == '.') {
                streak++;
            } else {
                streak = 0;
            }
            streakUp[j][i] = streak;
        }
    }
}

int Fence::computePerimeter() {
    preprocess();
    
    int peri=0;
    
    for (int mi=0; mi<M; mi++) {
        for (int ni=0; ni<N; ni++) {
            if (land[mi][ni] == 'x') continue;
            int fromn = ni - streakLeft[mi][ni] + 1, fromm=mi - streakUp[mi][ni] + 1;
            for (int thism=fromm; thism<mi; thism++) {
                for (int thisn=fromn; thisn<ni; thisn++) {
                    if ((streakLeft[thism][ni] >= (ni-thisn+1)) && (streakUp[mi][thisn] >= (mi-thism+1))) {
                        int perim = 2*(ni-thisn+1) + 2*(mi-thism+1) - 4;
                        if (perim > peri) {
                            peri = perim;
                        }
                    }
                }
            }
        }
    }
    return peri;
}

int main() {
    int m, n; std::cin >> m >> n;
    Fence fence(m, n);
    int perimeter = fence.computePerimeter();
    if (perimeter >= 4) {
        std::cout << perimeter << std::endl;    
    } else {
        std::cout << "impossible" << std::endl;
    }   
}

