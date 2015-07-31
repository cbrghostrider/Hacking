// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>
#include <assert.h>

using std::vector;

class ChiefHopper {
public:
    ChiefHopper(int n);
    long long energyNeeded();
private:
    void readInput();
    long long solveForBuilding(long long afterEnergy, int bind);
    vector<int> buildings;
};

ChiefHopper::ChiefHopper(int n) 
: buildings(n, 0) {
    readInput();
}

void ChiefHopper::readInput() {
    for (int i=0; i<buildings.size(); i++) {
        std::cin >> buildings[i];
    }
}

long long ChiefHopper::solveForBuilding(long long afterEnergy, int bind) {
    long long delta = afterEnergy + buildings[bind];
    return (delta/2 + delta%2);
}


long long ChiefHopper::energyNeeded() {
    long long energy = 0;
    for (int i=buildings.size()-1; i>=0; i--) {
        energy = solveForBuilding(energy, i);
    }
    return energy;
}

int main() {
    int n; std::cin >> n;
    ChiefHopper ch(n);
    std::cout << ch.energyNeeded() << std::endl;
}
