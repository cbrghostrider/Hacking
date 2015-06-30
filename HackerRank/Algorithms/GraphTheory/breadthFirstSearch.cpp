// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <queue>

using std::unordered_set;
using std::vector;
using std::queue;

class BFSShortestPaths {
public:
    BFSShortestPaths();
    void printShortestPaths();
private:
    void readInput();
    void findShortestPaths();
    vector<unordered_set<int>> adjList;
    vector<int> hops;
    int startNode;
};

BFSShortestPaths::BFSShortestPaths()
: adjList(),  startNode(0), hops() {
    readInput();
}

void BFSShortestPaths::readInput() {
    int m, n; std::cin >> n >> m;

    adjList = vector<unordered_set<int>>(n, unordered_set<int>());
    hops = vector<int>(n, -1);

    for (int i=0; i<m; i++) {
        int st, end; std::cin >> st >> end;
        int stp = st-1, endp = end-1; //make 0 indexed
        adjList[stp].insert(endp);
        adjList[endp].insert(stp);
    }

    std::cin >> startNode; startNode -= 1;//make 0 indexed
}

void BFSShortestPaths::findShortestPaths() {
    vector<bool> visited(hops.size(), false);
    hops[startNode] = 0;

    queue<int> bfsqueue;
    bfsqueue.push(startNode);
    visited[startNode] = true;

    while (!bfsqueue.empty()) {
        int node = bfsqueue.front(); bfsqueue.pop();
        for (const int& neighbor : adjList[node]) {
            if (visited[neighbor]) continue;
            hops[neighbor] = hops[node] + 1;
            visited[neighbor] = true;
            bfsqueue.push(neighbor);
        }
    }
}

void BFSShortestPaths::printShortestPaths() {
    findShortestPaths();

    for (int i=0; i<hops.size(); i++) {
        if (i == startNode) continue; 
        int length = hops[i];
        if (length != -1) length *= 6;
        std::cout << length << " ";
    }
    std::cout << std::endl;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        BFSShortestPaths paths;
        paths.printShortestPaths();
    }
}

