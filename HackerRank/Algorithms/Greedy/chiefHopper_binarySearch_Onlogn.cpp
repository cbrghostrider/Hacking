// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Binary search O(n log n) is too slow (only 7/15 tests pass, other time out TLE)
// But it was still fun coding it.. will try greedy next
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

class ChiefHopper {
public:
    ChiefHopper(int n);
    long long energyNeeded();
private:
    void readInput();
    bool simulateBot(long long startEnergy);
    long long binarySearch(long long start, long long end);
    vector<int> buildings;
    long long globalCtr;
    long long curEnergy;
};

ChiefHopper::ChiefHopper(int n) 
: buildings(n, 0), globalCtr(0), curEnergy(0) {
    readInput();
}

void ChiefHopper::readInput() {
    for (int i=0; i<buildings.size(); i++) {
        std::cin >> buildings[i];
    }
}

bool ChiefHopper::simulateBot(long long startEnergy) {
    int curEnergy = startEnergy;
    for (int b=0; b<buildings.size(); b++) {
        if (curEnergy < buildings[b]) {
            curEnergy -= (buildings[b] - curEnergy);
        } else {
            curEnergy += (curEnergy - buildings[b]);
        }
        if (curEnergy < 0) {
            return false;
        }
    }
    return true;
}

long long ChiefHopper::binarySearch(long long minval, long long maxval) {
    if (simulateBot(minval)) {
        return minval;
    }
    long long midval  = (minval + maxval)/2;
    long long midplus = midval+1;
    if (simulateBot(midval)) {
        return binarySearch(minval, midval);
    }
    return binarySearch(midplus, maxval);
}

long long ChiefHopper::energyNeeded() {
    long long max = 0;
    for (int b=0; b<buildings.size(); b++) {
        if (buildings[b] > max) {
            max = buildings[b];
        }
    }
    return binarySearch(0, max);
}

int main() {
    int n; std::cin >> n;
    ChiefHopper ch(n);
    std::cout << ch.energyNeeded() << std::endl;
}


