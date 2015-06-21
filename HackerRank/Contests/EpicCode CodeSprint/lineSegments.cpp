// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------

// Warning!
// only partially correct, need to debug some test cases, 
// uploading for future reference
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using std::vector;
using std::pair;
using std::make_pair;


struct Line {
    int begin;
    int end;
    Line(int b=0, int e=0) : begin(b), end(e) {}
};

class LineSegment {
private:
    vector<Line> segments; 

    bool badPair(const Line& l1, const Line& l2);
    void readInput(int n);
public:
    LineSegment(int n);
    int biggestSubset();
};

LineSegment::LineSegment(int n)
: segments(n, Line()) {
    readInput(n);
}

void LineSegment::readInput(int n) {
    for (int i=0; i<n; i++) {
        int b, e; std::cin >> b >> e;
        segments[i].begin = b;
        segments[i].end = e;
    }
}

bool LineSegment::badPair(const Line& l1, const Line& l2) {
    bool l1Coversl2 = (l1.begin <= l2.begin && l1.end >= l2.end);
    bool l2Coversl1 = (l2.begin <= l1.begin && l2.end >= l1.end);
    return (l1Coversl2 || l2Coversl1);
}

int LineSegment::biggestSubset() {
    //sort line segments on earliest end
    std::sort(segments.begin(), segments.end(), [] (const Line& lhs, const Line& rhs) -> bool {
        if (lhs.end != rhs.end) {
            return (lhs.end < rhs.end);
        } else {
            return (lhs.begin > rhs.begin);
        }
    });

    pair<int, Line> sofar = make_pair(1, segments[0]); 

    for (int i=1; i<segments.size(); i++) {
        if (badPair(sofar.second, segments[i])) continue;
        sofar.first++;
        sofar.second = segments[i];
    }
    return sofar.first;
}

int main() {
    int num;
    std::cin >> num;

    LineSegment ls(num);
    int ans = ls.biggestSubset();
    std::cout << ans << std::endl;
}

