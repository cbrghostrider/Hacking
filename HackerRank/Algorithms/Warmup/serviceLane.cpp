// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

using std::vector;
using std::pair;
using std::make_pair;

class Highway {
    const int BIKE, CAR, TRUCK;
    vector<int> serviceLane;
    vector<pair<int, int>> testCases;
    int checkVehicle(int enter, int exit);
    int runTestCase(int tc);
public:
    Highway();
    void readHighway();
    void runTestCases();
    ~Highway();
};

Highway::Highway()
: BIKE(1), CAR(2), TRUCK(3), serviceLane() {        
}

Highway::~Highway() {
}

void Highway::readHighway() {
    int n, t;
    std::cin >> n >> t;
    for (int i=0; i<n; i++) {
        int lane;
        std::cin >> lane;
        serviceLane.push_back(lane);
    }
    for (int i=0; i<t; i++) {
        int enter, exit;
        std::cin >> enter >> exit;
        testCases.push_back(make_pair(enter, exit));
    }
}

int Highway::checkVehicle(int enter, int exit) {
    if (enter < 0 || exit < 0 || enter >= serviceLane.size() || exit >= serviceLane.size() || enter > exit) return BIKE;
    bool truckPossible = true, carPossible = true;
    for (int i=enter; i<=exit; i++) {
        if (serviceLane[i] < TRUCK) truckPossible = false;
        if (serviceLane[i] < CAR) carPossible = false;
    }
    return (truckPossible ? TRUCK : (carPossible ? CAR : BIKE));
}

int Highway::runTestCase(int tc) {
    if (tc < 0 || tc >= testCases.size()) return BIKE;
    return (checkVehicle(testCases[tc].first, testCases[tc].second));
}

void Highway::runTestCases() {
    for (int i=0; i<testCases.size(); i++) {
        int ans = runTestCase(i);
        std::cout << ans << std::endl;
    }
}

int main() {
    Highway highway;
    highway.readHighway();
    highway.runTestCases();
    return 0;
}

