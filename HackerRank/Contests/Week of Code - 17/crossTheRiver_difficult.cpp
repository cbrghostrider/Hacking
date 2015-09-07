// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(n^2) dynamic programming algorithm
// 19/21 test cases AC (accepted), 2/21 TLE (time out)
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

typedef long long Points; //points per rock
typedef int Dim;          //x and y dimensions

const Points DONOTJUMP = -100000000; //max negative points for rocks where we should not jump

struct Rock {
    Dim y;
    Dim x;
    Points points;
    Rock(Dim yi, Dim xi, Points pts) : y(yi), x(xi), points(pts) {}
};

class CrossTheRiver {
public:
    CrossTheRiver(int N, Dim H, Dim dH, Dim dW);
    Points maxScore();
private:
    void readInput(int N);
    void findBestAlloc(int index);
    const Dim H, dH, dW;
    vector<Rock> rocks;
    vector<Points> points; //the points gained by jumping up to this rock
};

CrossTheRiver::CrossTheRiver(int N, Dim H_, Dim dH_, Dim dW_) 
: H(H_), dH(dH_), dW(dW_), rocks(), points(N, DONOTJUMP) {
    readInput(N);
}

void CrossTheRiver::readInput(int N) {
    Dim x, y;
    Points pts;
    rocks.reserve(N);
    for (int i=0; i<N; i++) {
        std::cin >> y >> x >> pts;
        Rock rock(y, x, pts);
        rocks.push_back(rock);
    }
}

//find best allocation for this rock
void CrossTheRiver::findBestAlloc(int index) {
    Points max = (rocks[index].y + dH >= H) ? rocks[index].points : points[index];
    for (int jumpto=index+1; jumpto < rocks.size(); jumpto++) {
        if (rocks[index].y + dH < rocks[jumpto].y) break;         //only choose rocks within dH
        if (rocks[index].y == rocks[jumpto].y) continue;          //Important: continue coz may find other rocks
        if (abs(rocks[index].x - rocks[jumpto].x) > dW) continue; //Important: continue coz may find other rocks
        Points thesePoints = rocks[index].points + points[jumpto];
        if (thesePoints > max) max = thesePoints;
    }
    points[index] = max;
}

//DP algorithm starting from the rocks nearest to the shore at H
Points CrossTheRiver::maxScore() {
    //sort rocks on y
    std::sort(rocks.begin(), rocks.end(), [] (const Rock& lhs, const Rock& rhs) -> bool {
        if (lhs.y != rhs.y) {
            return (lhs.y < rhs.y);
        } else {
            return (lhs.x < rhs.x);
        }
    });

    //base case for points
    int index=rocks.size()-1;
    for (; index>=0; index--) {
        if (rocks[index].y < H-dH) break; //can't jump from this rock to shore
        findBestAlloc(index);
    }

    //DP algorithm
    for (; index >=0 ; index--) {
        findBestAlloc(index);
    }

    //find best points among rocks that I can jump to from my side of the shore
    Points retval = DONOTJUMP;
    for (int i=0; i<rocks.size(); i++) {
        if (rocks[i].y - dH > 0) break;
        if (points[i] > retval) retval = points[i];
    }
    return retval;
}

int main() {
    int N;
    Dim H, dH, dW;
    std::cin >> N >> H >> dH >> dW;

    CrossTheRiver ctr(N, H, dH, dW);
    Points mp = ctr.maxScore();
    std::cout << mp << std::endl;
}

