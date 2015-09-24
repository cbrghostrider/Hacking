// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <cfenv>

using std::unordered_set;
using std::unordered_map;
using std::pair;
using std::make_pair;
using std::vector;

typedef int Weight;
typedef int Node;

struct Edge {
    Node from;
    Node to;
    Weight weight;
    Edge (Node f, Node t, Weight w) : from(f), to(t), weight(w) {}
};

typedef vector<Edge> Bucket;
typedef vector<Bucket> AdjList;

class Quantum {
public:
    Quantum(int n);
    void expectation();
private:
    void readInput();
    bool dfs(Node d, Node& cycAt);
    void examinePotCycle(Node cycAt);

    const int N;
    AdjList adjList;
    vector<bool> visited;
    vector<Edge> eStack;
    vector<double> candidates;
};

Quantum::Quantum(int n) 
: N(n), adjList(N, Bucket()), visited(N), candidates() {
    readInput();
}

void Quantum::readInput() {
    for (Node from=0; from<N; from++) {
        Node to; std::cin >> to; 
        to -= 1; //0-indexed
        Weight wt; std::cin >> wt;
        adjList[from].push_back(Edge(from, to, wt));
    }
}

//ret value indicates potential cycle found
bool Quantum::dfs(Node node, Node& cycAt) {
    if (visited[node]) {
        cycAt = node;
        return true;
    }

    visited[node] = true;

    if (adjList[node].size()) {
        eStack.push_back(adjList[node][0]);
        bool recval = dfs(adjList[node][0].to, cycAt);
        if (recval) { return true;}
        eStack.pop_back();
    }

    return false;
}

void Quantum::examinePotCycle(Node cycAt) {
    double candidate = 1;

    for (int i=eStack.size()-1; i>=0; i--) {
        double myEdge = ((double)eStack[i].weight)/100.0;
        candidate *= myEdge;
        if (eStack[i].from == cycAt) { //found cycle
            candidates.push_back(candidate);
            return;
        }
    }
    return; //no cycle found
}

void Quantum::expectation() {
    for (int i=0; i<N; i++) {
        if (!visited[i]) {
            Node cycAt = -1;
            bool rec = dfs(i, cycAt);
            if (rec) { examinePotCycle(cycAt);}
            eStack.clear();
        }
    }
    double expVal = 0;
    for (double& cand : candidates) {
        expVal += cand;
    }
    printf("%.2f\n", expVal);
}

int main() {
    fesetround(FE_TONEAREST);
    //int val = fegetround();
    //std::cout << val << std::endl;
    int n; std::cin >> n;
    Quantum q(n);
    q.expectation();
}


