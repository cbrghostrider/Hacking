// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <unordered_set>
#include <algorithm>

using std::unordered_set;
using std::vector;
using std::pair;
using std::make_pair;

//both inclusive [left, right]
struct Range {
    int left;
    int right;
    int size() const {return (right - left + 1);}
    Range(int l, int r) : left(l), right(r) {}
    Range& operator=(const Range& rhs) {
        left = rhs.left;
        right = rhs.right;
        return *this;
    }
};

class Circle {
public:
    Circle(Range r);
    ~Circle();
    void addCircle(Circle* in);  //in is inscribed within this Circle
    bool contains(int id);       //directly or indirectly 
    bool containsDirectly(int id);
    bool containsIndirectly(int id);
    void findStrongPairs(vector<pair<int, int>>& sps);
    Range getRange() const {return range;}

private:
    Range range;                 //directly or indirectly in circle
    vector<Circle*> inscribed;   //inside this Circle
};

Circle::Circle(Range rr)
: range(rr),
  inscribed() {
}

Circle::~Circle() {
    for (Circle* i : inscribed) {
        delete i;
    }
}

void Circle::addCircle(Circle* in) {
    inscribed.push_back(in);
}

bool Circle::contains(int id) {
    return (id >= range.left && id <= range.right);
}

bool Circle::containsIndirectly(int id) {
    if (!contains(id)) return false;
    for (Circle* c : inscribed) {
        if (c->contains(id)) return true;
    }
    return false;
}

bool Circle::containsDirectly(int id) {
    if (!contains(id)) return false;
    if (containsIndirectly(id)) return false;
    return true;
}

void Circle::findStrongPairs(vector<pair<int, int>>& sps) {
    for (Circle* c : inscribed) {
        int numinside = c->range.left;
        if (c->containsDirectly(numinside)) {
            int numcheck = numinside + 1;
            if (containsDirectly(numcheck)) {
                sps.push_back(make_pair(numinside, numcheck));
            }
            numcheck = numinside - 1;
            if (containsDirectly(numcheck)) {
                sps.push_back(make_pair(numcheck, numinside));
            }
        }
        
        if (c->range.left == c->range.right) continue;

        numinside = c->range.right;
        if (c->containsDirectly(numinside)) {
            int numcheck = numinside + 1;
            if (containsDirectly(numcheck)) {
                sps.push_back(make_pair(numinside, numcheck));
            }
            numcheck = numinside - 1;
            if (containsDirectly(numcheck)) {
                sps.push_back(make_pair(numcheck, numinside));
            }
        }
    }
    
    for (Circle * c : inscribed) {
        c->findStrongPairs(sps);
    }
}

class CodingCamp {
public:
    CodingCamp(int n, int m);
    ~CodingCamp();
    void countStrongPairs();
private:
    void readRanges();
    void drawCircles();
    const int N, M;
    vector<pair<int, Range>> ranges;
    vector<Circle*> circles;         //camp is a collection of circles
};

CodingCamp::CodingCamp(int n, int m)
: N(n), M(m) {
    readRanges();
}

CodingCamp::~CodingCamp() {
    for (Circle* c : circles) {
        delete c;
    }
}

void CodingCamp::readRanges() {
    for (int m=0; m<M; m++) {
        int left, right; std::cin >> left >> right;
        left -= 1; right -= 1; //0-indexed
        ranges.push_back(make_pair(ranges.size(), Range(left, right)));
    }
}

void CodingCamp::drawCircles() {
    std::sort(ranges.begin(), ranges.end(), [] (const pair<int, Range>& lhs, const pair<int, Range>& rhs) -> bool {
        if (lhs.second.size() != rhs.second.size()) {
            return (lhs.second.size() < rhs.second.size());
        } else {
            return (lhs.first < rhs.first);
        }
    });

    for (int ri=0; ri<M; ri++) {
        Range range = ranges[ri].second;
        vector<Range> rtaken;

        Circle *thiscircle = new Circle(range);
        vector<Circle*> circlesprime;

        for (int i=0; i<circles.size(); i++) {
            if (!(circles[i]->getRange().left >= range.left && circles[i]->getRange().right <= range.right)) {
                circlesprime.push_back(circles[i]);
                continue;
            }
            thiscircle->addCircle(circles[i]);
            rtaken.push_back(circles[i]->getRange());
        }

        circlesprime.push_back(thiscircle);
        circles = circlesprime;

        std::sort(rtaken.begin(), rtaken.end(), [] (const Range& lhs, const Range& rhs) -> bool {
            if (lhs.left != rhs.left) {
                return (lhs.left < rhs.left);
            } else {
                return (lhs.right < rhs.right);
            }
        });
    }
}

void CodingCamp::countStrongPairs() {
    drawCircles();

    vector<pair<int, int>> sps;
    for (Circle* c : circles) {
        c->findStrongPairs(sps);
    }
    for (int i=0; i<sps.size(); i++) {
        if (sps[i].first > sps[i].second) {
            int temp = sps[i].first;
            sps[i].first = sps[i].second;
            sps[i].second = temp;
        }
    }
    std::sort(sps.begin(), sps.end(), [] (const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
        if (lhs.first != rhs.first) {
            return (lhs.first < rhs.first);
        } else {
            return (lhs.second < rhs.second);
        }
    });

    std::cout << sps.size() << std::endl;

    for (int i=0; i<sps.size(); i++) {
        std::cout << (sps[i].first + 1) << " " << (sps[i].second + 1) << std::endl;
    }
}

int main() {
    int n, m; std::cin >> n >> m;
    CodingCamp cc(n, m);
    cc.countStrongPairs();
}

