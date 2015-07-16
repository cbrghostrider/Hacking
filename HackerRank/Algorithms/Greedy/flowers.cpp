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

class Flowers {
public:
    Flowers();
    int payMoney();
private:
    void readInput();
    vector<int> flowers;
    int K;
};

Flowers::Flowers() 
: flowers(), K(0) {
    readInput();
}

void Flowers::readInput() {
    int n; std::cin >> n >> K;
    for (int i=0;i<n; i++) {
        int flower; std::cin >> flower;
        flowers.push_back(flower);
    }
} 

int Flowers::payMoney() {
    std::sort(flowers.begin(), flowers.end(), std::greater<int>());
    int cost=0;
    
    for (int i=0;i<flowers.size(); i++) {
        int adder=i/K;
        cost += (adder + 1)*flowers[i];
    }
    return cost;
}

int main() {
    Flowers flowers;
    int cost = flowers.payMoney();
    std::cout << cost << std::endl;
}

