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
using namespace std;

class Problem {
private:
    int N_;
    int K_;
    string enc_;
    string result_;
    
    inline char exor(char a, char b) {return ((a == b) ? '0' : '1');}
    char fillKM1MSB_();   //fill in the (k-1) MSB values, returns final xor of those (K-1) bits
public:
    Problem();
    ~Problem() {}
    
    void solveProblem();
    
    friend istream& operator>>(istream& in, Problem& pb);
    friend ostream& operator<<(ostream& out, const Problem& pb);
};

Problem::Problem() 
: N_(0), K_(0), enc_(), result_() {
}

istream& operator>>(istream& in, Problem& pb) {
    in >> pb.N_ >> pb.K_;
    in >> pb.enc_;
    return in;
}

ostream& operator<<(ostream& out, const Problem& pb) {
    out << pb.result_;
    return out;
}

char Problem::fillKM1MSB_() {
    char acc = '0';
    for (int i=0; i < K_-1; i++) {
        char bit = exor(acc, enc_[i]);
        acc = exor(bit, acc);
        result_.push_back(bit);
    }
    return acc;
}

void Problem::solveProblem() {
    result_.reserve(N_);
    
    //fill (K-1) MSBs, and find xor of those values
    char acc = fillKM1MSB_();
    char drop = '0'; //drop this guy, while xor-ing in new guy
    for (int i=K_-1; i<N_; i++) {
        char bit = exor(acc, enc_[i]);
        drop = result_[result_.size() - K_+1];
        acc = exor(exor(acc, drop), bit);
        result_.push_back(bit);
    }
}

int main() {
    Problem pb;
    std::cin >> pb;
    pb.solveProblem();
    std::cout << pb << std::endl;;
    return 0;
}
