// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// This version did not solve the problem as dfs was too slow, 
// and also lack of stack space caused seg fault
//
// Including here just for completeness
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>

using std::vector;

typedef int Node;
typedef long long Weight;

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
    bool dfs(Node from, Node to, Weight k, Weight costSoFar, long long countSoFar);
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
    return dfs(from, to, k, 0, 0);
}

bool Corro::dfs(Node from, Node to, Weight k, Weight costSoFar, long long countSoFar) {
    //std::cout << "Cmae from " << from+1 << std::endl;
    if (from == to) {
        return true;   //found some result (T/F: In this case T)
    }
    visited[from] = true;
    for (const Edge& e : adjList[from]) {
        if (visited[e.to]) continue;

        Weight totalWt = costSoFar + e.wt;
        long long totalCnt = countSoFar + 1;
        //std::cout << "comparing totalwt " << totalWt << " with (k * totalcnt)" << (k*totalCnt) << std::endl;
        if (totalWt > (k * totalCnt)) {
            continue;
        }
        if (dfs(e.to, to, k, totalWt, totalCnt)) {
            visited[from] = false;
            return true; //result is passed on 
        }
    }

    visited[from] = false;
    return false; //exhausted this dfs search
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


