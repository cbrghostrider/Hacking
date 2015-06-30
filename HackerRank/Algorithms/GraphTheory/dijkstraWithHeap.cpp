// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <utility>
#include <functional>
#include <queue>

using std::priority_queue;
using std::pair;
using std::make_pair;
using std::vector;
using std::set;

typedef unsigned int Node;
typedef int Weight;

struct Edge {
    Node to;
    Weight weight;
    Edge(Node t, Weight w) : to(t), weight(w) {}
};

typedef pair<Node, Edge> QuElem;

class Dijkstra {
public:
    Dijkstra();
    void printShortestPaths();
private:
    void readInput();
    void runDijkstra();
    Node startNode;
    vector<vector<Edge> > adjList;
    vector<Weight> pathLens;
};

Dijkstra::Dijkstra()
: startNode(0), adjList(), pathLens() {
    readInput();
}

void Dijkstra::readInput() {
    int n, m; std::cin >> n >> m;
    adjList = vector<vector<Edge> >(n, vector<Edge>());
    pathLens = vector<Weight>(n, -1);

    for (int i=0; i<m; i++) {
        Node start, end; std::cin >> start >> end;
        Weight wt; std::cin >> wt;
        start -= 1; end -= 1; //make 0-indexed
        adjList[start].push_back(Edge(end, wt));
        adjList[end].push_back(Edge(start, wt));
    }

    std::cin >> startNode; startNode -= 1; //make 0-indexed
}

void Dijkstra::runDijkstra() {
    //compare function for minimum heap
    std::function<bool (const QuElem&, const QuElem& )> HeapCompare = 
      [this] (const QuElem& lhs, const QuElem& rhs) -> bool {
          return ((pathLens[lhs.first]+lhs.second.weight) > (pathLens[rhs.first]+rhs.second.weight));
      };

    //the minimum heap for edges on the frontier
    priority_queue<QuElem, vector<QuElem>, decltype(HeapCompare)> frontier(HeapCompare);

    //to mark which ones are already done
    vector<bool> processed(adjList.size(), false);

    //initialize starting conditions
    pathLens[startNode] = 0;
    processed[startNode] = true;
    for (const Edge& edge : adjList[startNode]) frontier.push(make_pair(startNode, edge));

    bool done = false;
    
    while (!done && !frontier.empty()) {
        QuElem cand = frontier.top(); frontier.pop();
        while (processed[cand.second.to]) {
            //because C++ priority_queue has no API to delete non-min element, I am forced to do this
            if (frontier.empty()) {done = true; break;}
            cand = frontier.top(); frontier.pop();
        }
        if (done) break;

        //this node now has its shortest path determined
        Node absorb = cand.second.to;
        pathLens[absorb] = pathLens[cand.first] + cand.second.weight;
        processed[absorb] = true;

        //add this node's edges to frontier
        for (const Edge& edge : adjList[absorb]) {
            frontier.push(make_pair(absorb, edge));
        }
    }
}

void Dijkstra::printShortestPaths() {
    //run dijkstra's shortest paths algorithm
    runDijkstra();

    //and print the results
    for (int i=0; i<adjList.size(); i++) {
        if (i == startNode) continue;
        std::cout << pathLens[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        Dijkstra dijkstra;
        dijkstra.printShortestPaths();
    }
}
