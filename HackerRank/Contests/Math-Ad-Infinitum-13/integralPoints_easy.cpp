// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <math.h>

typedef long long Units;

struct Point {
    Units x;
    Units y;
    Point(Units xi=0, Units yi=0) : x(xi), y(yi) {}
};

Units twiceArea(Point p1, Point p2, Point p3) {
    Units ans = 0;
    ans += (-1)*p2.y * p3.x;
    ans += p1.y*((-1)*p2.x + p3.x);
    ans += p1.x*(p2.y - p3.y);
    ans += p2.x * p3.y;
    return ((ans >= 0 ) ? ans : (-1)*ans);
}

Units gcd (Units a, Units b ) {
    if (a > b) return gcd(b, a);
    if (a == b) return a;

    Units c;
    while (a != 0) {
        c = a; a = b%a;  b = c;
    }
    return b;
}

inline Units absdiff(Units v1, Units v2) {
    return ((v1 > v2) ? (v1-v2): (v2-v1));
}

Units findBoundaryPoints(Point p1, Point p2, Point p3) {
    Units b = 0;
    b += gcd(absdiff(p1.x, p2.x), absdiff(p1.y, p2.y));
    b += gcd(absdiff(p2.x, p3.x), absdiff(p2.y, p3.y));
    b += gcd(absdiff(p3.x, p1.x), absdiff(p3.y, p1.y));
    return b;
}

Units findInteriorPoints(Point p1, Point p2, Point p3) {
    Units tarea = twiceArea(p1, p2, p3);
    Units b     = findBoundaryPoints(p1, p2, p3);
    Units ans   = (tarea - b + 2) / 2;
    return (ans);
}

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        Point p1, p2, p3;
        std::cin >> p1.x >> p1.y;
        std::cin >> p2.x >> p2.y;
        std::cin >> p3.x >> p3.y;
        Units ans = findInteriorPoints(p1, p2, p3);
        std::cout << ans << std::endl;
    }
}
