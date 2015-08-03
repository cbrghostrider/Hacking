// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// This version did not solve the problem either as it was too slow
// Basically I moved from dfs to bfs to avoid the stack space issue
// Only 2 test cases passed, rest TLE
// Including here just for completeness
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <queue>
#include <utility>

using std::queue;
using std::pair;
using std::make_pair;
using std::vector;

typedef int Node;
typedef long long Weight;

struct Info {
    Weight wtSoFar;
    long long cntSoFar;
    Info(int w, int c) : wtSoFar(w), cntSoFar(c) {}
};

struct Edge {
    Node to; 
    Weight wt;
    Edge (Node nt, Weight w) : to(nt), wt(w) {}
};

class Corro {
public:
    Corro(int n);
    bool processQuery(Node from, Node to, Weight k);
private:
    void readInput();
    void clearMarks();
    bool bfs(Node from, Node to, Weight k);
    int N;
    vector<vector<Edge>> adjList;
    vector<bool> visited;
};

Corro::Corro(int n) 
: N(n), adjList(N, vector<Edge>()), visited(N, false) {
    readInput();
}

void Corro::readInput() {
    for (int i=0; i<N-1; i++) {
        Node from, to; std::cin >> from >> to;
        from -=1; to -= 1; //0-indexed
        Weight wt; std::cin >> wt;

        adjList[from].push_back(Edge(to, wt));
        adjList[to].push_back(Edge(from, wt));
    }
}

void Corro::clearMarks() {
    for (int i=0; i<N; i++) {
        visited[i] = false;
    }
}

bool Corro::processQuery(Node from, Node to, Weight k) {
    clearMarks();
    //std::cout << "------------------------" << std::endl;
    return bfs(from, to, k);
}

bool Corro::bfs(Node from, Node to, Weight k) {
    queue<pair<Node, Info>> bfsqu;
    bfsqu.push(make_pair(from, Info(0, 0)));
    visited[from] = true;

    while (!bfsqu.empty()) {
        auto bfselem = bfsqu.front(); bfsqu.pop();

        for (const Edge e: adjList[bfselem.first]) {
            if (visited[e.to]) continue;
            visited[e.to] = true;
            Weight checkWt = e.wt + bfselem.second.wtSoFar;
            long long checkCnt = 1 + bfselem.second.cntSoFar;

            if (checkWt > (checkCnt * k)) {
                continue;
            }

            if (e.to == to) {
                return true; //found a way to get here!
            }

            pair<Node, Info> nip = make_pair(e.to, Info(checkWt, checkCnt));
            bfsqu.push(nip);
        }
    }

    return false;
}

int main() {
    int n, q; std::cin >> n >> q;
    Corro corro(n);
    for (int i=0; i<q; i++) {
        Node from, to; std::cin >> from >> to;
        from -= 1; to -= 1; 
        Weight k; std::cin >> k;
        bool ans = corro.processQuery(from, to, k);
        std::cout << (ans ? "YES" : "NO") << std::endl;
    }
}


