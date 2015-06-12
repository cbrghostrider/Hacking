// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using std::vector;

class Graph {
private:
    int nverts;
    int nedges;
    vector<vector<int> > adjList;
    vector<int> subTreeSize;
    void readGraph();
    void computeSubtreeSizes();
    int treeSize(int vert);
public:
    Graph();
    ~Graph();
    int countBreaks();  
};

Graph::Graph() 
: nverts(0), nedges(0), adjList(), subTreeSize(){
    readGraph();
}

Graph::~Graph() {
}

void Graph::readGraph() {
    std::cin >> nverts >> nedges;
    
    adjList = vector<vector<int>>(nverts, vector<int>());
    subTreeSize = vector<int>(nverts, 0);
    
    for (int i=0; i<nedges; i++) {
        int child, parent;
        std::cin >> child >> parent;
        adjList[parent-1].push_back(child-1);
    }
}

//compute size of subtree rooted at each vertex has
void Graph::computeSubtreeSizes() {
    for (int v=0; v<nverts; v++) {
        if (subTreeSize[v] == 0) {
            subTreeSize[v] = treeSize(v);
        }
    }
}

int Graph::treeSize(int v) {
    if (subTreeSize[v] == 0) { //not computed yet
        if (adjList[v].size() == 0) {
            subTreeSize[v] = 1; //this is a leaf
        } else {
            int sum=1; //myself
            for (int& child : adjList[v]) {
                sum += treeSize(child);
            }
            subTreeSize[v] = sum; //this is a node
        }
    }
    return subTreeSize[v];
}

int Graph::countBreaks() {
    computeSubtreeSizes();
    int breaks=0;
    for (int v=0; v<nverts; v++) {
        for (int& child : adjList[v]) {
            if ((subTreeSize[child] % 2) == 0) { //I can break this link
                breaks++;
            }
        }
    }
    return breaks;
}

int main() {
    Graph graph;
    int ans = graph.countBreaks();
    std::cout << ans << std::endl;
}

