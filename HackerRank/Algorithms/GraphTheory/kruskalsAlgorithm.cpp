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

/////////////////////////////////////////////////////////////////////////////////////////
//                           Union Find data structure
/////////////////////////////////////////////////////////////////////////////////////////

class QuickUnion {
public:
    ~QuickUnion() {}
    QuickUnion(const int numKeys);           //adds each key into its own set
    void Union(const int k1, const int k2);  //unions two sets
    int Find(const int k) const;             //finds what set is this key
    int NumSets() const;                     //returns number of sets in DS
    int maxSet() const;                      //returns the size of the maximum set in the UF
private:
    int Root_(int index) const;
    vector<int> arr_;     //each key associated with its set here
    vector<int> sz_;      //size of each tree rooted here
};

QuickUnion::QuickUnion(const int numKeys) 
: arr_(), sz_() {
    for (int i=0; i<numKeys; i++) {
        arr_.push_back(i);
        sz_.push_back(1); 
    }
}

int QuickUnion::Root_(int index) const {
    while (index != arr_[index]) {
        index = arr_[index];
    }
    return index;
}

void QuickUnion::Union(const int kf, const int kt) {
    int from = Root_(kf);
    int to   = Root_(kt);
    if (from == to) return;
    if (sz_[from] < sz_[to]) {
        arr_[from] = to;
        sz_[to] += sz_[from];
    } else {
        arr_[to] = from;
        sz_[from] += sz_[to];
    }
}

int QuickUnion::Find(const int k) const {
    return Root_(k);
}

int QuickUnion::NumSets() const {
    vector<int> examine;
    for (int i=0; i<arr_.size(); i++) {
        examine.push_back(Root_(i));
    }
    
    std::sort(examine.begin(), examine.end());
    auto newend = std::unique(examine.begin(), examine.end());
    int ctr=0;
    for (auto it=examine.begin(); it != newend; it++) {
        ctr++;
    }
    return ctr;
}

int QuickUnion::maxSet() const {
    int max = 0;
    for (int i=0; i<arr_.size(); i++) {
        if (i == Root_(i)) {
            if (max < sz_[i]) {
                max = sz_[i];
            }
        }
    }
    return max;
}

/////////////////////////////////////////////////////////////////////////////////////////
//                           Kruskals algorithm
/////////////////////////////////////////////////////////////////////////////////////////


class KruskalsAlgorithm {
public:
    KruskalsAlgorithm();
    Weight mstWeight();
private:
    void readInput();
    int numNodes;
    Node startNode;
    vector<Edge> edges;
};

KruskalsAlgorithm::KruskalsAlgorithm() 
: numNodes(0), startNode(0) ,edges() {
    readInput();
}

void KruskalsAlgorithm::readInput() {
    int n, m; std::cin >> n >> m;
    numNodes = n;

    for (int i=0; i<m; i++) {
        Node from, to; std::cin >> from >> to;
        from -= 1; to -= 1; //make 0 indexed
        Weight wt; std::cin >> wt;
        edges.push_back(Edge(from, to, wt));
    }
    std::cin >> startNode; startNode -= 1; //make 0 indexed
}

Weight KruskalsAlgorithm::mstWeight() {
    priority_queue<Edge, vector<Edge>, EdgeCompare> minHeap;
    vector<Edge> mstEdges;
    QuickUnion uf(numNodes);

    for (const Edge& e : edges) { minHeap.push(e);}

    while (!minHeap.empty()) {
        Edge edge = minHeap.top(); minHeap.pop();
        if (uf.Find(edge.from) == uf.Find(edge.to)) continue;
        mstEdges.push_back(edge);
        uf.Union(edge.from, edge.to);
    }

    Weight sum = 0;
    for (const Edge& e : mstEdges) sum += e.weight;

    return sum;
}

int main() {
    KruskalsAlgorithm kruskals;
    Weight ans = kruskals.mstWeight();
    std::cout << ans << std::endl;
}


