// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>

using std::vector;

class SumAbsolutes {
public:
    SumAbsolutes();
    void runQueries();
private:
    void readInput();
    void evalFunc();
    int runQuery(int l, int r);

    int nqueries;
    vector<int> nums;
    vector<int> eval;
};

SumAbsolutes::SumAbsolutes()
: nums(), eval() {
    readInput();
}

void SumAbsolutes::readInput() {
    int n; std::cin >> n >> nqueries;
    for (int i=0; i<n; i++) {
        int ai; std::cin >> ai;
        nums.push_back(ai);
    }
}

void SumAbsolutes::evalFunc() {
    int sum = 0;
    for (int i=0; i<nums.size(); i++) {
        sum = abs(sum + nums[i]);
        eval.push_back(sum);
    }
}

void SumAbsolutes::runQueries() {
    evalFunc();
    for (int i=0; i<nqueries; i++) {
        int l, r; std::cin >> l >> r;
        l -= 1; r -= 1; //0-indexed
        int interim = runQuery(l, r);
        if (interim % 2) {
            std::cout << "Odd" << std::endl;
        } else {
            std::cout << "Even" << std::endl;
        }
    }
}

int SumAbsolutes::runQuery(int l, int r) {
    if (l == 0) return eval[r];
    int evalr   = eval[r];
    int evallm1 = eval[l-1];
    int interim = 0;
    if (nums[l] >= 0) {
        interim = abs(evalr - evallm1);
    } else if (evallm1 >= abs(nums[l])) {
        interim = abs(evalr + 2*abs(nums[l]) - evallm1);
    } else {
        interim = evalr + evallm1;
    }
    return interim;
}

int main() {
    SumAbsolutes sa;
    sa.runQueries();
}
