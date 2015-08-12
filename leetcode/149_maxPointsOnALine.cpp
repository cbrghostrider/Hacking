// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// O(n^2) algorithm
//
// This code currently passes on my local machine, but leetcode online judge says it is executing incorrectly.
// e.g. for the test case currently in main, my code on the local machine correctly outputs 3 as the answer.
// But leetcode OJ complains that my output is 2 and 3 is expected, for the same test case.
// Not sure what is going on, hopefully it isn't some cryptic bug.
// I am including the code for completeness, btw, this was a really cool problem!
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <limits>
#include <functional>

using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::pair;
using std::make_pair;
using std::hash;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

bool operator==(const Point& lhs, const Point& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

class Line {
public:
    Line(Point p1, Point p2);
    bool operator==(const Line& rhs) const {return (a == rhs.a && b == rhs.b && c == rhs.c);}
    int a;
    int b;
    int c;
};

int Gcd (int v1, int v2) {
  int c;
  int a = std::min(v1, v2);
  int b = std::max(v1, v2);
  while (a != 0) {
     c = a; a = b%a;  b = c;
  }
  return b;
}

Line::Line(Point p1, Point p2) 
: a(0), b(0), c(0) {
    if (p1.x == p2.x) {
        a = 1;
        b = 0;
        c = -1 * p1.x;
        return;
    } else if (p1.y == p2.y) {
        a = 0;
        b = 1;
        c = -1 * p1.y;
        return;
    }
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = p1.x*p2.y - p2.x*p1.y;

    if (c == 0) {
        int gcd = Gcd(a, b);
        a = a / gcd;
        b = b / gcd;
    } else {
        int gcd = Gcd(a, Gcd(b, c));
        a = a / gcd;
        b = b / gcd;
        c = c / gcd;
    }
    if (a < 0) { //so that we can compare easily
        a *= -1;
        b *= -1;
        c *= -1;
    }
}

typedef unsigned int U32;
typedef unsigned long long U64;
typedef int PtCounts;
typedef unordered_map<Line, PtCounts> CacheElem;

namespace std {
    template<>
    struct hash<Line> {
        unsigned long long operator () (const Line& line) const {
            ((((U64)line.a) << 32) ^ (((U64)line.b) << 16) ^ ((U64)line.c)); //is this a good hash?
        }
    };
    template<>
    struct hash<Point> {
        unsigned long long operator() (const Point& pt) const {
            U32 xval = pt.x;
            U32 yval = pt.y;
            return ((((U64) xval) << 32) | ((U64) yval));
        }
    };
}

class MaxPoints {
public:
    MaxPoints(const vector<Point>& pts);
    int maxPoints();
private:
    int maxPoints_();
    vector<Point> points;
    CacheElem cache;
    unordered_map<Point, int> uniquePts;
};

MaxPoints::MaxPoints(const vector<Point>& pts)
: points(pts), cache(), uniquePts() {
}

int MaxPoints::maxPoints_() {
    if (points.size() == 0) return 0;
    if (points.size() == 1) return uniquePts[points[0]];

    //Base case: Two points are always collinear
    Line line01(points[0], points[1]);
    cache.insert(make_pair(line01, uniquePts[points[0]] + uniquePts[points[1]]));

    for (int cand=2; cand<points.size(); cand++) {   //check for collinearity of this point with others
        Point& candidate = points[cand];
        unordered_set<Line> processed;

        for (int i=cand-1; i>=0; i--) {
            //construct a line passing through cand and point i
            Line newline(candidate, points[i]);
            
            //if I already have processed this line, then leave
            auto myit = processed.find(newline); 
            if (myit != processed.end()) continue;
            processed.insert(newline);
            
            auto fit = cache.find(newline);
            if (fit != cache.end()) { 
                //if prevcache has this line, add this point to set of already collinear points
                cache[newline] += uniquePts[points[cand]]; //adding cand
            } else {
                //if not, this is a new line I have seen so add these two points to it
                cache.insert(make_pair(newline, uniquePts[points[cand]] + uniquePts[points[i]])); //for cand and point i
            }
        }
    }

    int maxpoints = 0;
    for (auto ce : cache) {
        if (ce.second > maxpoints) {
            maxpoints = ce.second;
        }
    }
    return maxpoints;
}

int MaxPoints::maxPoints() {
    std::sort(points.begin(), points.end(), [] (const Point& lhs, const Point& rhs) -> bool {
        if (lhs.x != rhs.x) {
            return (lhs.x < rhs.x);
        } else if (lhs.y != rhs.y) {
            return (lhs.y < rhs.y);
        }
        return false;
    });
    for (const Point& pt : points) {
        if (uniquePts.find(pt) == uniquePts.end()) {
            uniquePts.insert(make_pair(pt, 1));
        } else {
            uniquePts[pt]++;
        }
    }
    auto it = std::unique(points.begin(), points.end(), [] (const Point& lhs, const Point& rhs) -> bool {
        return (lhs.x == rhs.x && lhs.y == rhs.y);
    });
    points.erase(it, points.end());
    return maxPoints_();
}

class Solution {
public:
    int maxPoints(vector<Point>& points) {

        MaxPoints mp(points);
        return mp.maxPoints();
    }
};

int main() {
    /*
    Point pt0(0, 0);
    Point pt1(0, 1);
    Point pt2(1, 0);
    Point pt3(1, 1);
    Point pt4(2, 2);
    vector<Point> points = {pt0, pt1, pt2, pt3, pt4};
    */
    /*
    Point pt1(-4, 1);
    Point pt2(-7, 7);
    Point pt3(-1, 5);
    Point pt4(9, -25);
    vector<Point> points = {pt1, pt2, pt3, pt4};
    */
    Point pt2(0, 0);
    Point pt3(-1, -1);
    Point pt4(2, 2);
    vector<Point> points = {pt2, pt3, pt4};
    
    MaxPoints mp(points);
    int ans = mp.maxPoints();
    std::cout << ans << std::endl;
}

