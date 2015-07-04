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

using std::vector;

typedef unsigned int Elem;

class MissingNumbers {
public:
    MissingNumbers();
    void printMissingNumbers();
private:
    void readInput();
    const Elem MaxBucketSize;
    vector<Elem> ns;
    vector<Elem> ms;
};

MissingNumbers::MissingNumbers()
: MaxBucketSize(101), ns(), ms() {
    readInput();
}

void MissingNumbers::printMissingNumbers() {
    vector<Elem> bucketN(MaxBucketSize, 0);
    vector<Elem> bucketM(MaxBucketSize, 0);
    
    Elem minElem = std::numeric_limits<Elem>::max();
    for (int i=0; i<ns.size(); i++) if (ns[i] < minElem) minElem = ns[i];
    
    for (int i=0; i<ns.size(); i++) bucketN[ns[i] - minElem] += 1; 
    for (int i=0; i<ms.size(); i++) bucketM[ms[i] - minElem] += 1; 
    for (int i=0; i<MaxBucketSize; i++) {
        if (bucketN[i] != bucketM[i]) {
            std::cout << i+minElem << " ";
        }
    }
    std::cout << std::endl;
}

void MissingNumbers::readInput() {
    int n, m; std::cin >> n;
    for (int i=0; i<n; i++) {
        Elem elem; std::cin >> elem;
        ns.push_back(elem);
    }
    std::cin >> m;
    for (int i=0; i<m; i++) {
        Elem elem; std::cin >> elem;
        ms.push_back(elem);
    }
}

int main() {
    MissingNumbers mn;
    mn.printMissingNumbers();
}

