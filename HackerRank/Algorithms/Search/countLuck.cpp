// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// Note that this is really a graph search problem, and not binary search
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <limits>
#include <queue>
#include <utility>

using std::pair;
using std::make_pair;
using std::queue;
using std::string;
using std::vector;
using std::unordered_set;
using std::unordered_map;

typedef unsigned int PInd;        //r or c index 
typedef unsigned long long PRepr; //key for (r, c)

struct Point {
    PInd rn;
    PInd cn;
    PRepr operator() () {return ((((PRepr)rn) << 32) | ((PRepr)cn));}
    bool operator==(const Point& rhs) {return (rn == rhs.rn && cn == rhs.cn);}
    Point(PInd r, PInd c) : rn(r), cn(c) {}
};

class ForestGraph {
public:
    ForestGraph();
    void validateGuess();
private:
    void readInput();
    void constructGraph();
    PInd rows, cols;
    int k;
    Point start, end;             
    vector<string> forest;
    unordered_map<PRepr, unordered_set<PRepr>> adjList;
};

ForestGraph::ForestGraph() 
: rows (0), cols(0), k(0), start(0,0), end(0,0), forest(), adjList() {
    readInput();
    constructGraph();
}

void ForestGraph::readInput() {
    std::cin >> rows >> cols;
    for (PInd i=0; i<rows; i++) {
        string str; std::cin >> str;
        forest.push_back(str);
    }
    std::cin >> k;
}

void ForestGraph::constructGraph() {
    for (PInd r=0; r<rows; r++) {
        for (PInd c=0; c<cols; c++) {
            Point me(r, c);
            adjList[me()] = unordered_set<PRepr>();
        }
    }
    
    for (PInd r=0; r<rows; r++) {
        for (PInd c=0; c<cols; c++) {
            if (forest[r][c] == 'X') continue; //trees don't connect to anyone           
            Point me(r, c);
            if (forest[r][c] == 'M') { start = me;}
            if (forest[r][c] == '*') { end = me;}
            
            if (r != 0 && forest[r-1][c] != 'X') {//check up
                Point up(r-1, c);
                adjList[me()].insert(up());
                adjList[up()].insert(me());
            }                       
            if (c != 0 && forest[r][c-1] != 'X') {//check left
                Point left(r, c-1);
                adjList[me()].insert(left());
                adjList[left()].insert(me());
            }                        
        }
    }
}

void ForestGraph::validateGuess() {
    int guess = 0;
    vector<vector<PInd>> visited(rows, vector<PInd>(cols, false));
    
    queue<pair<int, Point>> bfsqu;
    bfsqu.push(make_pair(0, start));
    visited[start.rn][start.cn] = true;
    
    while (!bfsqu.empty()) {
        auto myinfo = bfsqu.front(); bfsqu.pop();
        int curLen = myinfo.first;
        Point me = myinfo.second;
        if (me == end) {guess = curLen; break;}
        
        for (const PRepr& pr : adjList[me()]) {
            PInd r = ((PInd)(pr >> 32));
            PInd c = ((PInd)(pr & 0xFFFFFFFF));
            if (visited[r][c]) continue;
            visited[r][c] = true;
            
            //came from one place, will go to one place,
            //if I have another option, then need to wave wand
            int delta = 0;
            if (me == start && adjList[me()].size() > 1) {
                delta = 1;
            } else if (adjList[me()].size() > 2) {
                delta = 1;
            } 
            
            bfsqu.push(make_pair(curLen + delta, Point(r, c)));
        }
    }
    
    std::cout << (guess == k ? "Impressed" : "Oops!") << std::endl;  
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        ForestGraph fg;
        fg.validateGuess();
    }
}

