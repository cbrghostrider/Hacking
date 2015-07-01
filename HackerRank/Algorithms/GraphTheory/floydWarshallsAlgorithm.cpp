// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits>

using std::vector;

typedef int Weight;
typedef int Node;

struct Edge {
    Node from;
    Node to;
    Weight weight;
    Edge(Node f, Node t, Weight w) : from(f), to(t), weight(w) {}
};

class FloydWarshallsAlgorithm {
public:
    FloydWarshallsAlgorithm();
    void computeShortestPaths();
    Weight pathLen(Node from, Node to);
private:
    void readInput();
    int numNodes;
    vector<Edge> edges;
    vector<vector<Weight>> cache;
};

FloydWarshallsAlgorithm::FloydWarshallsAlgorithm() 
: numNodes(0), edges(), cache() {
    readInput();
}

void FloydWarshallsAlgorithm::readInput() {
    int n, m; std::cin >> n >> m;
    numNodes = n;
    cache = vector<vector<Weight>>(n, vector<Weight>(n, std::numeric_limits<Weight>::max()));

    for (int i=0; i<m; i++) {
        Node from, to; std::cin >> from >> to;
        from -= 1; to -= 1; //make 0 indexed
        Weight wt; std::cin >> wt;
        auto it = std::find_if(edges.begin(), edges.end(), [from, to] (const Edge& e) -> bool {
            return (from == e.from && to == e.to);
        });
        if (it == edges.end()) {
            edges.push_back(Edge(from, to, wt));
        } else {
            *it = Edge(from, to, wt);
        }
    }
}

Weight FloydWarshallsAlgorithm::pathLen(Node from, Node to) {
    Weight wt = cache[from][to];
    return (wt == std::numeric_limits<Weight>::max() ? -1 : wt);
}

void FloydWarshallsAlgorithm::computeShortestPaths() {
    //dynamic programming initialization steps
    for (int i=0; i<numNodes; i++) { cache[i][i] = 0;}
    for (const Edge& edge : edges) { cache[edge.from][edge.to] = edge.weight; }

    //meat of dynamic programming algorithm
    for (int k=0; k < numNodes; k++) {
        for (int f=0; f<numNodes; f++) {
            for (int t=0; t<numNodes; t++) {
                if (cache[f][k] == std::numeric_limits<Weight>::max() ||
                    cache[k][t] == std::numeric_limits<Weight>::max()) {
                    continue;
                }
                Weight candidate = cache[f][k] + cache[k][t];
                if (cache[f][t] > candidate) {
                    cache[f][t] = candidate;
                }
            }
        }
    }
}

int main() {
    FloydWarshallsAlgorithm fw;
    fw.computeShortestPaths();
    int queries; std::cin >> queries;
    for (int q=0; q<queries; q++) {
        Node from, to; std::cin >> from >> to;
        from -=1; to -=1; //0-indexed
        std::cout << fw.pathLen(from, to) << std::endl; 
    }
}
