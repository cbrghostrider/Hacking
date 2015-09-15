// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

using std::string;
using std::vector;

typedef long long Ways;
typedef unsigned char U8;

const bool VALID   = true;
const bool INVALID = false;

const U8 OBSTACLE = 0xAD;
const U8 FREE     = 0;
const U8 BISHOP   = 0xBE;

class BishopWar {
public:
    BishopWar(int n, int m);
    Ways computeWays();
private:
    void readInput();
    inline bool onBoard(int r, int c) const;
    inline bool matchChar(int r, int c, U8 ch) const;
    void mark(int r, int c, bool isValid);
    void markTraverse(int r, int c, int rd, int cd, U8 value); 
    void printBoard() const;
    Ways dfs(int rowNum);

    const int N, M;
    vector<vector<U8>> board; //numeric valid denotes # of bishops attacking this cell, 
                               //others are bishop, obstacle, free
};

BishopWar::BishopWar(int n, int m)
:N(n), M(m), board(N, vector<U8>(M, 0)) {
    readInput();
}

void BishopWar::readInput() {
    string str;
    for (int i=0; i<N; i++) {
        std::cin >> str;
        for (int c=0; c<M; c++) {
            switch(str[c]) {
                case '*': {
                    board[i][c] = OBSTACLE;
                    break;
                }
                case '.': {
                    board[i][c] = FREE;
                    break;
                }
            }
        }
    }
}

inline bool BishopWar::matchChar(int r, int c, U8 ch) const {
    return (board[r][c] == ch);
}

inline bool BishopWar::onBoard(int r, int c) const {
    return ((r >= 0) && (r < N) && (c >= 0) && (c < M));
}

void BishopWar::markTraverse(int r, int c, int rd, int cd, U8 value) {
    for (int ri = r+rd, ci = c+cd; onBoard(ri, ci); ri+=rd, ci+=cd) {
        if (board[ri][ci] == OBSTACLE) break;
        board[ri][ci] += value;
    }
}

void BishopWar::mark(int r, int c, bool isValid) {   
    //printBoard();
    U8 value = isValid ? -1 : 1;
    //if (r >= N/2) { //odd numbered, move upwards
        markTraverse(r, c, -1, -1, value);
        markTraverse(r, c, -1,  1, value);
    //} else {     //even numbered move downwards
        markTraverse(r, c,  1, -1, value);    
        markTraverse(r, c,  1,  1, value);
    //}
}

void BishopWar::printBoard() const {
    std::cout << "---------------------------------" << std::endl;
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            std::cout << board[i][j] ;
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
}

//place bishop in this row in all possible ways
Ways BishopWar::dfs(int rowNum) {
    int delta = rowNum/2; //delta from the central line
    int midrow = ((N-1)/2);
    int myrow = (rowNum % 2) ? (midrow + 1 + delta) : (midrow - delta);
    
    if (rowNum == N-1) {
        Ways retval = 0;
        for (int ci=0; ci<M; ci++) {
            if (board[myrow][ci] == FREE) retval++;
        }
        return retval;
    }
    
    Ways retval = 0;
    for (int c=0; c<M; c++) {
        if (!(matchChar(myrow, c, FREE))) continue;

        //place bishop here
        board[myrow][c] = BISHOP;
        mark(myrow, c, INVALID);

        retval += dfs(rowNum + 1);

        //unplace bishop here
        board[myrow][c] = FREE;
        mark(myrow, c, VALID);
    }
    return retval;
}

Ways BishopWar::computeWays() {
    return dfs(0);
}

int main() {
    int N, M; std::cin >> N >> M;
    BishopWar bw(N, M);
    Ways ways = bw.computeWays();
    std::cout << ways << std::endl;
}

