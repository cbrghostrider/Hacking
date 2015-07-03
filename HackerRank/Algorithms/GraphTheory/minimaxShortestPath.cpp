// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// The minimax path problem is a special case of the widest path problem
// which is a special case of the shortest path problem
// Basically, we are trying to find the shortest path from A to B subject
// to the constraint that "shortest" is defined as the path with the 
// minimum maximum edge cost. 
// i.e. of all the paths possible from A to B, find the maximum edge along
// each of those paths, and then choose the one path that gives the 
// minimum such maximum edge
// 
// To find this, we can just find the minimum spanning tree, and then do a 
// BFS or DFS to find the maximum edge along the path from A to B
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

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

class MinimaxPath {
public:
    MinimaxPath();
    Weight minFare();
private:
    void readInput();
    vector<Edge> minimumSpanningTreeEdges();
    void constructMST();
    bool dfs(Node node, Weight& wt);

    Node numNodes, startNode, endNode;
    vector<vector<Edge>> adjList;
    vector<vector<Edge>> MST;
    vector<bool> visited;
};

MinimaxPath::MinimaxPath() 
: numNodes(0), startNode(0), endNode(0), adjList(), MST(), visited() {
    readInput();
}

void MinimaxPath::readInput() {
    int n, e; std::cin >> n >> e;
    numNodes = n; startNode = 0; endNode = n-1;
    adjList = vector<vector<Edge>>(n, vector<Edge>());
    visited = vector<bool>(n, false);

    for (int i=0; i<e; i++) {
        Node s1, s2; Weight c; 
        std::cin >> s1 >> s2 >> c;
        adjList[s1-1].push_back(Edge(s1-1, s2-1, c));
        adjList[s2-1].push_back(Edge(s2-1, s1-1, c));
    }
}

//runs prims algorithm to find the MST edges, for connected component including startNode
vector<Edge> MinimaxPath::minimumSpanningTreeEdges() {
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

    return mstEdges;
}

void MinimaxPath::constructMST() {
    vector<Edge> mstedges = minimumSpanningTreeEdges();
    MST = vector<vector<Edge>>(adjList.size(), vector<Edge>());

    //construct the MST
    for (const Edge& e: mstedges) {
        MST[e.from].push_back(Edge(e.from, e.to, e.weight));
        MST[e.to].push_back(Edge(e.to, e.from, e.weight));
    }
}

bool MinimaxPath::dfs(Node node, Weight& wt) {
    visited[node] = true;
    if (node == endNode) {
        wt = 0;
        return true;
    }

    for (Edge& neighedge : MST[node]) {
        Node neighbor = neighedge.to;
        if (visited[neighbor]) continue;

        bool retval = dfs(neighbor, wt);
        if (retval) { //found end in this dfs
            if (wt < neighedge.weight) { //adjust weight of max edge if needed
                wt = neighedge.weight;
            }
            return true;
        }
    }

    return false;
}

//perform a DFS of the MST to find min fare
Weight MinimaxPath::minFare() {
    constructMST();

    for (int i=0; i<visited.size(); i++) visited[i] = false;

    Weight retval = 0;
    bool found = dfs(startNode, retval);

    return (found ? retval : 0);
}

int main() {
    MinimaxPath mmp;
    Weight ans = mmp.minFare();
    if (ans) {
        std::cout << ans << std::endl;
    } else {
        std::cout << "NO PATH EXISTS" << std::endl;
    }
}
