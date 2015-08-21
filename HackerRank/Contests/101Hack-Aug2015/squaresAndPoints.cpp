// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>

using std::pair;
using std::make_pair;
using std::vector;

typedef long long Dim;

struct Point {
    Dim px;
    Dim py;
    Point(Dim x, Dim y) : px(x), py(y) {}
};

class Square {
public:
    Square(Point p, Dim len);
    bool containsPoint(Point pq);
    Dim cornerX() const {return pt.px;}
    Dim cornerY() const {return pt.py;}
private:
    Point pt;
    Dim len;
};

Square::Square(Point p, Dim length)
: pt(p), len(length) {
}

bool Square::containsPoint(Point pq) {
    int px = pq.px;
    int py = pq.py;
    int x = pt.px;
    int y = pt.py;
    return ((px >= x && px <= (x + len)) && (py >= y && py <= (y+len)) );
}


class Problem {
public:
    Problem();
    int solveProblem();
private:
    template <typename FUNC> int binSearchFuncDim(int from, int to, Dim val, FUNC func, bool isx);

    //returns start and end indices within square(x/y) for squares that may contain this pt(x/y)
    pair<int, int> searchSquaresOn(Dim val, bool isx);

    //returns how many squares contain this point 
    int squaresForPoint(Point p);

    void initialize();
    void sortOnX(vector<pair<Square, int>>& sq);
    void sortOnY(vector<pair<Square, int>>& sq);

    int N, M;
    Dim L;
    vector<Square> squares;
    vector<Point> points;
    vector<int> squaresx; //indices
    vector<int> squaresy; //indices
};

Problem::Problem()
: N(0), M(0), L(0), squares(), points(), squaresx(), squaresy() {
    std::cin >> N >> M >> L;

    for (int i=0; i<N; i++) {
        Dim x, y; std::cin >> x >> y;
        squares.push_back(Square(Point(x, y), L));
    }
    for (int i=0; i<M; i++) {
        Dim x, y; std::cin >> x >> y;
        points.push_back(Point(x, y));
    }

    initialize();
}

void Problem::sortOnX(vector<pair<Square, int>>& sq) {
    std::sort(sq.begin(), sq.end(), [] (const pair<Square, int>& lhs, const pair<Square, int>& rhs) -> bool {
        if (lhs.first.cornerX() != rhs.first.cornerX()) {
            return (lhs.first.cornerX() < rhs.first.cornerX());
        } else if (lhs.first.cornerY() != rhs.first.cornerY()) {
            return (lhs.first.cornerY() < rhs.first.cornerY());
        }
        return false;
    });
    for (int i=0; i<sq.size(); i++) {
        squaresx.push_back(sq[i].second);
    }
}

void Problem::sortOnY(vector<pair<Square, int>>& sq) {
    std::sort(sq.begin(), sq.end(), [] (const pair<Square, int>& lhs, const pair<Square, int>& rhs) -> bool {
        if (lhs.first.cornerY() != rhs.first.cornerY()) {
            return (lhs.first.cornerY() < rhs.first.cornerY());
        } else if (lhs.first.cornerX() != rhs.first.cornerX()) {
            return (lhs.first.cornerX() < rhs.first.cornerX());
        }
        return false;
    });
    for (int i=0; i<sq.size(); i++) {
        squaresy.push_back(sq[i].second);
    }
}

void Problem::initialize() {
    vector<pair<Square, int>> squaresxp, squaresyp;
    for (int i=0; i<squares.size(); i++) {
        squaresxp.push_back(make_pair(squares[i], i));
        squaresyp.push_back(make_pair(squares[i], i));
    }
    sortOnX(squaresxp);
    sortOnY(squaresyp);
}

template <typename FUNC>
int Problem::binSearchFuncDim(int from, int to, Dim val, FUNC func, bool isx) {
    if (from > to) return -1;
    vector<int>& sq = (isx ? squaresx : squaresy);
    std::function<Dim (int)> ExtractVal = [&sq, isx, this] (int index) -> Dim {
        return (isx ? squares[sq[index]].cornerX() : squares[sq[index]].cornerY());
    };
    if (from == to) {
        if (func(ExtractVal(from), val)) {
            return from;
        } else {
            return -1;
        }
    }
    int mid     = (from+to)/2;
    int midplus = mid + 1;
    if (func(ExtractVal(mid), val)) return binSearchFuncDim(from, mid, val, func, isx);
    return binSearchFuncDim(midplus, to, val, func, isx);
}

pair<int, int> Problem::searchSquaresOn(Dim val, bool isx) {
    vector<int>& sq = (isx ? squaresx : squaresy);

    //how many squares end at or after this point in this dimension
    std::function<bool (Dim, Dim)> gteq = [this] (Dim lhs, Dim rhs) -> bool {return ((lhs+L) >= rhs);}; 

    //how many squares start after this point
    std::function<bool (Dim, Dim)> gt   = [] (Dim lhs, Dim rhs) -> bool {return (lhs > rhs);};

    int from = binSearchFuncDim(0, squares.size()-1, val, gteq, isx);
    int to   = binSearchFuncDim(0, squares.size()-1, val, gt  , isx);

    return make_pair(from, to);
}

int Problem::squaresForPoint(Point p) {
    pair<int, int> xft = searchSquaresOn(p.px, true);
    pair<int, int> yft = searchSquaresOn(p.py, false);

    //no squares end at or after x (or y) coordinate of point p
    if (xft.first == -1 || yft.first == -1) return 0;

    //all squares start after this point (x or y)
    if (xft.second == 0 || yft.second == 0) return 0;

    vector<int> sqx, sqy, inter;
    std::copy(squaresx.begin() + xft.first, (xft.second == -1 ? squaresx.end() : squaresx.begin() + xft.second), back_inserter(sqx));
    std::copy(squaresy.begin() + yft.first, (yft.second == -1 ? squaresy.end() : squaresy.begin() + yft.second), back_inserter(sqy));

    //sort both on x
    std::sort(sqx.begin(), sqx.end());
    std::sort(sqy.begin(), sqy.end());

    std::set_intersection(sqx.begin(), sqx.end(), sqy.begin(), sqy.end(), back_inserter(inter), [this] (const int lhs, const int rhs) -> bool {
        return (lhs < rhs);
    });

    return inter.size();
}

int Problem::solveProblem() {
    int count = 0;
    for (int i=0; i<M; i++) {
        int cnt = squaresForPoint(points[i]);
        if (cnt > count) count = cnt;
    }
    return count;
}

int main() {
    Problem p;
    int ans = p.solveProblem();
    std::cout << ans << std::endl;
}


