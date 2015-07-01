// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>

using std::pair;
using std::make_pair;
using std::vector;
using std::priority_queue;

typedef int Weight;
typedef int Node;

struct Edge {
    Node from;
    Node to;
    Weight weight;
    Edge(Node f, Node t, Weight w) : from(f), to(t), weight(w) {}
};

class EdgeCompare {
public:
    bool operator () (const Edge& lhs, const Edge& rhs) {
        return (lhs.weight > rhs.weight);
    }
};

class PrimsAlgorithm {
public:
    PrimsAlgorithm();
    Weight mstWeight();
private:
    void readInput();
    Node startNode;
    vector<vector<Edge>> adjList;
    vector<bool> visited;
};

PrimsAlgorithm::PrimsAlgorithm() 
: startNode(0) ,adjList(), visited() {
    readInput();
}

void PrimsAlgorithm::readInput() {
    int n, m; std::cin >> n >> m;

    adjList = vector<vector<Edge>>(n, vector<Edge>());
    visited = vector<bool>(n, false);

    for (int i=0; i<m; i++) {
        Node from, to; std::cin >> from >> to;
        from -= 1; to -= 1; //make 0 indexed

        Weight wt; std::cin >> wt;
        adjList[from].push_back(Edge(from, to, wt));
        adjList[to].push_back(Edge(to, from, wt));
    }
    std::cin >> startNode; startNode -= 1; //make 0 indexed
}

Weight PrimsAlgorithm::mstWeight() {
    priority_queue<Edge, vector<Edge>, EdgeCompare> minHeap;

    for (const Edge& edge : adjList[startNode]) minHeap.push(edge);
    visited[startNode] = true;

    vector<Edge> mstEdges;
    bool done = false;

    while (!done && !minHeap.empty()) {
        Edge edge = minHeap.top(); minHeap.pop();

        //C++ heaps API cannot delete random element inside itself, therefore need this workaround
        while (visited[edge.from] && visited[edge.to]) {
            if (minHeap.empty()) {done = true; break;}
            edge = minHeap.top(); minHeap.pop();
        }
        if (done == true) break;

        mstEdges.push_back(edge); //adding this edge to MST
        Node addme = edge.to; 
        visited[addme] = true; //marking this node as done

        for (const Edge& e : adjList[addme]) {minHeap.push(e);}
    }

    Weight sum = 0;
    for (const Edge& e : mstEdges) sum += e.weight;

    return sum;
}

int main() {
    PrimsAlgorithm prims;
    Weight ans = prims.mstWeight();
    std::cout << ans << std::endl;
}
