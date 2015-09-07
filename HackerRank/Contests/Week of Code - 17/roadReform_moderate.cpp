// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(n^2) algorithm, 
// 34/41 test cases AC (accepted), 7/41 TLE (timing out)
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <queue>
#include <assert.h>

using std::priority_queue;
using std::pair;
using std::make_pair;
using std::hash;
using std::vector;

typedef int Node;
typedef long long Weight;
typedef long long Ways;

struct Edge {
    Node to;
    Weight weight;
    Edge(Node t, Weight w) : to(t), weight(w) {}
};

typedef vector<Edge> Bucket;
typedef vector<Bucket> AdjList;

typedef pair<Weight, Edge> DjPair;
struct HeapCmp {
    bool operator() (const DjPair& lhs, const DjPair& rhs) {
        return (lhs.first > rhs.first);
    }
};

typedef priority_queue<DjPair, vector<DjPair>, HeapCmp> MinHeap;

class RoadReform {
public:
    RoadReform(int n, int m);
    Ways computeWays();
private:
    void runDijkstra(Node from, vector<Weight>& djdata);
    void readInput();
    Ways computeXPathWays(Weight spLength);
    void displayShortestPath(Node nd, vector<Weight>& djdata);

    const int N, M;
    AdjList adjList;
    vector<Weight> fromData;
    vector<Weight> toData;
};

RoadReform::RoadReform(int n, int m)
: N(n), M(m), adjList(), fromData(N, Weight()), toData(N, Weight()) {
    readInput();
}

void RoadReform::readInput() {
    for (int i=0; i<N; i++)  {
        adjList.push_back(Bucket());
    }
    for (int i=0; i<M; i++) {
        Node from, to; Weight wt;
        std::cin >> from >> to >> wt;
        from -= 1; to -= 1; //make 0-indexed
        auto fit = std::find_if(adjList[from].begin(), adjList[from].end(), [to](const Edge& e) -> bool {
            return (e.to == to);
        });
        auto tit = std::find_if(adjList[to].begin(), adjList[to].end(), [from](const Edge& e) -> bool {
            return (e.to == from);
        });
        if (fit == adjList[from].end()) {     //no roads seen between these before
            adjList[from].push_back(Edge(to, wt));
            adjList[to].push_back(Edge(from, wt));
        } else if (fit->weight > wt) { //found a parallel road with lesser cost
            fit->weight = wt;
            tit->weight = wt;
        }
    }
}

void RoadReform::runDijkstra(Node from, vector<Weight>& djdata) {
    vector<bool> processed(N, false);
    MinHeap heap;

    heap.push(make_pair(0, Edge(from, 0)));

    while (!heap.empty()) {
        DjPair elem = heap.top(); heap.pop();
        if (processed[elem.second.to]) continue;

        djdata[elem.second.to] = elem.first;
        processed[elem.second.to] = true;

        for (const Edge& aelem : adjList[elem.second.to]) {
            if (processed[aelem.to]) continue;
            heap.push(make_pair(elem.first + aelem.weight, aelem));
        }
    }
}

void RoadReform::displayShortestPath(Node nd, vector<Weight>& djdata) {
    std::cout << "shortest path from node " << nd << std::endl;
    for (int i=0; i<djdata.size(); i++) {
        std::cout << "-> " << i<< "; wt: " << djdata[i] << std::endl;
    }
}

//computes cross-paths such that there are two nodes x and y where:
// (path from from->x) + (path from y->to) is less than spLength, and x < y (to avoid duplication)
Ways RoadReform::computeXPathWays(Weight spLength) {
    Ways ways = 0;
    Node from = 0, to = N-1;
    vector<Weight> fromD, toD; 

    for (int i=0; i<N; i++) {
        if (fromData[i] >= spLength && toData[i] >= spLength) continue;
        fromD.push_back(fromData[i]);
        toD.push_back(toData[i]);
    }

    for (int i=0; i<fromD.size(); i++) {
        for (int j=i+1; j<fromD.size(); j++) {
            Weight from_i = fromD[i];
            Weight j_to   = toD[j];
            Weight from_j = fromD[j];
            Weight i_to   = toD[i];
            Weight cand1 = from_i + j_to;
            Weight cand2 = from_j + i_to;
            Weight cand  = std::min(cand1, cand2);
            if (cand >= spLength) continue;
            ways += (spLength - cand - 1);
        }
    }
    return ways;
}

Ways RoadReform::computeWays() {
    Node to = N-1, from = 0;
    runDijkstra(from, fromData);
    //displayShortestPath(from, fromData);
    runDijkstra(to, toData);
    //displayShortestPath(to, toData);

    Weight spLength = fromData[to];
    Ways xways = computeXPathWays(spLength);
    return xways;
}

int main() {
    int n, m; std::cin >> n >> m;
    RoadReform rr(n, m);
    Ways ans = rr.computeWays();
    std::cout << ans << std::endl;
}
