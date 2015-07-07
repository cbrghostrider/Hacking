// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
using namespace std;

class Tree {
public:
    Tree();
    ~Tree();
    int getMinTreeDiff();
private:
    void readInput();
    int computeSum(int node);
    void minTreeDiff(int root, const int total);
    void clearFlags();

    vector<int> vals;
    vector<int> sums;
    vector<bool> visited;
    vector<unordered_set<int>> adjList;
    int minsofar;
};

Tree::Tree() 
: vals(), sums(), visited(), adjList(), minsofar() {
    readInput();
}

Tree::~Tree() {
}

void Tree::clearFlags() {
    for (int i=0; i<visited.size(); i++) visited[i] = false; 
}

int Tree::computeSum(int node) {
    visited[node] = true;
    int childrensum = 0;
    for (const int& child : adjList[node]) {
        if (visited[child]) continue;
        childrensum += computeSum(child);
    }
    sums[node] = childrensum + vals[node];
    return sums[node];
}

int Tree::getMinTreeDiff() {
    minsofar = std::numeric_limits<int>::max();
    clearFlags();
    computeSum(0);
    clearFlags();
    minTreeDiff(0, sums[0]); //assuming node 0 is root
    return minsofar;
}

void Tree::minTreeDiff(int node, const int total) {
    visited[node] = true;
    for (const int& child : adjList[node]) {
        if (visited[child]) continue;
        int withoutchildsum = total - sums[child];
        int cand = abs(withoutchildsum - sums[child]);
        if (cand < minsofar) minsofar = cand;
        if ((withoutchildsum - sums[child] ) > minsofar) continue; //don't descend further
        minTreeDiff(child, total);
    }
}

void Tree::readInput() {
    int n; std::cin >> n;
    
    for (int i=0; i<n; i++) {
        int value; std::cin >> value;
        vals.push_back(value);
    }

    adjList = vector<unordered_set<int>>(n, unordered_set<int>());
    visited = vector<bool>(n, false);
    sums    = vector<int>(n, 0);

    for (int i=0; i<n-1; i++) {
        int n1, n2; std::cin >> n1 >> n2;
        n1 -= 1; n2 -= 1; //make 0 indexed
        adjList[n1].insert(n2);
        adjList[n2].insert(n1);
    }
}

int main() {
    Tree tree;
    int ans = tree.getMinTreeDiff();
    std::cout << ans << std::endl;
}

