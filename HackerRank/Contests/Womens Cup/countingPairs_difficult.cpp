// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <assert.h>

using std::vector;

typedef long long Elem;

const int MAXSIZE = 200001;

class CountPairs {
public:
    CountPairs(int n, int m, int q);
    void processQueries();
private:
    void processQuery();
    void runQuery1(int p1, int p2);
    void runQuery2(int p1, int p2);
    void runQuery3(int p1, int p2);

    const int N, M, Q;
    vector<int> as;
    vector<int> countas;
};

CountPairs::CountPairs(int n, int m, int q)
: N(n), M(m), Q(q), 
  as(N, 0),
  countas(MAXSIZE, 0) {
    for (int i=0; i<N; i++) {
        std::cin >> as[i];
        countas[as[i]]++;
    }
}

void CountPairs::processQueries() {
    for (int qi=0; qi<Q; qi++) {
        processQuery();
    }
}

void CountPairs::processQuery() {
    int type, p1, p2;
    std::cin >> type >> p1 >> p2;
    switch (type) {
      case 1: {
          runQuery1(p1, p2);
          break;
      }
      case 2: {
          runQuery2(p1, p2);
          break;
      }
      case 3: {
          runQuery3(p1, p2);
          break;
      }
      default: assert(0);
    }
}

void CountPairs::runQuery1(int index, int value) {
    index -= 1; //0-indexed
    countas[as[index]] -= 1;
    as[index] = value;
    countas[as[index]] += 1;
}

void CountPairs::runQuery3(int p1, int p2) {
    ;//nothing to do
}

void CountPairs::runQuery2(int s1, int s2) {
    Elem count = 0;
    if ((s2-s1) > as.size()) {
        for (const int& val : as) {
            int lhs = val + 1;
            int rhs = val + M;

            //[s1, s2] completely covers [lhs, rhs]
            if (s1 <= lhs && s2 >= rhs) {
                count += (rhs - lhs) + 1;
                continue;
            }

            //[lhs, rhs] completely covers [s1, s2]
            if (lhs <= s1 && rhs >= s2) {
                count += (s2 - s1) + 1;
                continue;
            }

            //disjoint
            if ((lhs > s2) || (rhs < s1)) {
                continue;
            }

            //overlapping
            int lv = std::max(lhs, s1);
            int rv = std::min(rhs, s2);
            count += (rv - lv) + 1;
        }
    } else {
        for (int i=std::max(0,s1-M); i<s1; i++) {
            int icnt = countas[i];
            int mycount = std::min(M, s2-i) - (s1 - i) + 1;
            count += (mycount * icnt);
        }
        for (int i=s1; i<=s2; i++) {
            int icnt = countas[i];
            int mycount = std::min(M, (s2 - i));
            count += (mycount * icnt);
        }
    }
    std::cout << count << std::endl;
}

int main() {
    int n, m, q; 
    std::cin >> n >> m >> q;

    CountPairs cp(n, m, q);
    cp.processQueries();
}



