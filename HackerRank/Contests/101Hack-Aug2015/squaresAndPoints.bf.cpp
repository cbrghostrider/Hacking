// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

typedef long long Dim;

class Square {
public:
    Square(Dim xi, Dim yi, Dim len);
    bool containsPoint(Dim px, Dim py);
private:
    Dim x;
    Dim y;
    Dim len;
};

Square::Square(Dim xi, Dim yi, Dim length)
: x(xi), y(yi), len(length) {
}

bool Square::containsPoint(Dim px, Dim py) {
    return ((px >= x && px <= (x + len)) && (py >= y && py <= (y+len)) );
}

struct Point {
    Dim px;
    Dim py;
    Point(Dim x, Dim y) : px(x), py(y) {}
};

class Problem {
public:
    Problem();
    int solveProblem();
private:
    int N, M;
    Dim L;
    vector<Square> squares;
    vector<Point> points;
};

Problem::Problem()
: N(0), M(0), L(0), squares(), points() {
    std::cin >> N >> M >> L;

    for (int i=0; i<N; i++) {
        Dim x, y; std::cin >> x >> y;
        squares.push_back(Square(x, y, L));
    }
    for (int i=0; i<M; i++) {
        Dim x, y; std::cin >> x >> y;
        points.push_back(Point(x, y));
    }
}

int Problem::solveProblem() {
    vector<int> counts(M, 0);
    for (int p=0; p<M; p++) {
        for (int s=0; s<N; s++) {
            if (squares[s].containsPoint(points[p].px, points[p].py)) {
                counts[p]++;
            }
        }
    }
    int count = 0;
    for (int p=0; p<M; p++) {
        if (counts[p] > count) {
            count = counts[p];
        }
    }
    return count;
}

int main() {
    Problem p;
    int ans = p.solveProblem();
    std::cout << ans << std::endl;
}
