// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// this problem is called Journey to the moon on hackerrank
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>

using std::vector;
using std::unordered_set;
using std::queue;

typedef int Node;

//computing the connected components of an undirected graph, using BFS/DFS
class ConnectedComponents {
public:
    ConnectedComponents();
    long long pickWays();
private:
    void readInput();
    vector<int> getCCSizes();
    vector<unordered_set<Node> > adjList;
};

ConnectedComponents::ConnectedComponents() 
: adjList() {
    readInput();
}

void ConnectedComponents::readInput() {
    int N, I; std::cin >> N >> I;
    adjList = vector<unordered_set<Node>>(N, unordered_set<Node>());

    for (int i=0; i<I; i++) {
        Node nd1, nd2; std::cin >> nd1 >> nd2;
        adjList[nd1].insert(nd2);
        adjList[nd2].insert(nd1);
    }
}

vector<int> ConnectedComponents::getCCSizes() {
    vector<int> retval;
    vector<bool> visited(adjList.size(), false);
    vector<int> ids(adjList.size(), 0);

    int id=0;
    for (int nd=0; nd<adjList.size(); nd++) {
        if (visited[nd]) continue;

        id++;              //new id for this connected component
        queue<Node> bfsqu; //bfs to find connected components
        visited[nd] = true;
        ids[nd] = id;
        bfsqu.push(nd);

        while (!bfsqu.empty()) {
            Node node = bfsqu.front(); bfsqu.pop();
            for (const Node& neighbor : adjList[node]) {
                if (visited[neighbor]) continue;
                visited[neighbor] = true;
                ids[neighbor] = id;
                bfsqu.push(neighbor);
            }
        }
    }

    std::sort(ids.begin(), ids.end());

    int curid = ids[0];
    int curCount = 1;
    for (int i=1; i<ids.size(); i++) {
        if (curid != ids[i]) {
            retval.push_back(curCount);
            curid = ids[i];
            curCount = 1;
        } else {
            curCount++;
        }
    }
    retval.push_back(curCount);

    return retval;
}

long long ConnectedComponents::pickWays() {
    vector<int> groups = getCCSizes();
    vector<long long> rcumsum(groups.size(), 0);

    long long cumsum=0;
    for (int i=groups.size()-1; i>=0; i--) {
        cumsum += groups[i];
        rcumsum[i] = cumsum;
    }

    long long retval=0;
    for (int i=0; i<groups.size()-1; i++) {
        retval += groups[i] * rcumsum[i+1];
    }

    return retval;
}

int main() {
    ConnectedComponents cc;
    long long ans = cc.pickWays();
    std::cout << ans << std::endl;
}


