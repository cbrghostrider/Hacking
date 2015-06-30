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

using std::queue;
using std::vector;
using std::unordered_set;

class DFSProbability {
private:
    vector<unordered_set<int>> adjList;
    vector<double> probabilities;
    void readInput();
    int destNode() const {return (adjList.size()-1);}
public:
    DFSProbability();
    double findProbability();
};

DFSProbability::DFSProbability()
: adjList() {
    readInput();
}

void DFSProbability::readInput() {
    int n, k, m; std::cin >> n;
    adjList = vector<unordered_set<int>>(n+1, unordered_set<int>());
    for (int i=0; i<n+1; i++) {
        std::cin >> k;
        for (int j=0; j<k; j++) {
            std::cin >> m;
            int src = i, dst = m-1;
            adjList[dst].insert(src);  //reverse the edge, so I can run search from the destination node
        }
    }
    double prob;
    for (int i=0; i<n; i++) {
        std::cin >> prob;
        probabilities.push_back(prob);
    }
    probabilities.push_back(0); //placeholder for (N+1)th node
}

double DFSProbability::findProbability() {
    vector<bool> visited(adjList.size(), false);

    queue<int> bfsqueue;
    bfsqueue.push(destNode());

    while (!bfsqueue.empty()) {
        const int& node = bfsqueue.front(); bfsqueue.pop();
        visited[node] = true;

        for (const int& neighbor : adjList[node]) {
            if (visited[neighbor]) continue;
            bfsqueue.push(neighbor);
        }
    }

    double prob = 0;
    for (int i=0; i<probabilities.size(); i++) {
        if (visited[i]) prob += probabilities[i];
    }

    return prob;
}

int main () {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        DFSProbability pp;
        double ans =  pp.findProbability();
        std::cout << (int)ans << std::endl;
    }
}
