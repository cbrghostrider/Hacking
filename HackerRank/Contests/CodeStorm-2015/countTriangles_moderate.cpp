// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using std::pair;
using std::make_pair;
using std::vector;
typedef long long Val;

class Triangles {
public:
    Triangles(int n);
    void findAnswers();
private:
    pair<int, int> findRange(int medind, int lhsind, int startind);
    void binSearchLocals(int hypind, int medind, int lhsind); 
    int binSearchSqr(Val target, int lo, int hi); 
    const int N;
    Val acute, right, obtuse;
    vector<Val> ns;
    vector<Val> nssqr;
};

Triangles::Triangles(int n) 
: N(n), 
  acute(0), right(0), obtuse(0),
  ns(N, 0), nssqr(N, 0) {
    for (int i=0; i<N; i++) {
        std::cin >> ns[i];
        nssqr[i] = ns[i] * ns[i];
    }
}

pair<int, int> Triangles::findRange(int medind, int lhsind, int startind) {
    const Val& val = ns[startind];
    int rlo=startind, rhi=startind;
    while (rlo >= lhsind && ns[rlo] == val) {rlo--;} 
    rlo++;
    while (rhi <= (medind-1) && ns[rhi] == val) {rhi++;} 
    rhi--;
    return make_pair(rlo, rhi);
}

//either finds the target, or return highest index < target
int Triangles::binSearchSqr(Val target, int lo, int hi) {
    if (lo == hi) {
        if (nssqr[lo] == target) {
            return lo;
        } else if (nssqr[lo] > target) {
            return lo-1;
        } else {
            return lo;
        }
    }

    int mid = (lo+hi)/2;
    if (nssqr[mid] == target) return mid;
    if (nssqr[mid] < target) {
        return binSearchSqr(target, mid+1, hi);
    }
    return binSearchSqr(target, lo, mid);
}

void Triangles::binSearchLocals(int hypind, int medind, int lhsind) {
    int lo = lhsind;
    int hi = medind-1;
    Val searchme = ns[hypind]*ns[hypind] - ns[medind]*ns[medind];
    int sind = binSearchSqr(searchme, lo, hi);

    if (sind == -1) { 
        acute += (hi - lo + 1);
    } else if (nssqr[sind] == searchme) {
        pair<int, int> range = findRange(medind, lhsind, sind);
        obtuse += (range.first - lhsind);
        right += (range.second - range.first + 1);
        acute += (medind - 1 - range.second);
    } else {
        obtuse += (sind - lhsind + 1);
        acute += (medind - 1 - sind);
    }
}

void Triangles::findAnswers() {
    for (int k=ns.size()-1; k>=0; k--) { //biggest side
        int lhsind = 0;
        for (int j=k-1; j>=0; j--) { //middle largest side
            while (lhsind < j && (ns[lhsind] + ns[j]) <= ns[k]) { //not a triangle
                lhsind++;
            }
            if (lhsind >= j) { break;}

            binSearchLocals(k, j, lhsind);
        }
    }
    std::cout << acute << " " << right << " " << obtuse << std::endl;
}

int main() {
    int n; std::cin >> n;
    Triangles t(n);
    t.findAnswers();
}

