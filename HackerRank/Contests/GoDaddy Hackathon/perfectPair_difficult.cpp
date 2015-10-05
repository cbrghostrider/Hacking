// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>

using std::unordered_set;
using std::vector;

typedef unsigned long long Key;
typedef unordered_set<int> Bucket;
typedef vector<Bucket> AdjList;

class PerfectPair {
public:
    PerfectPair(int n, int m, int q);
    void solve();
private:
    inline void clearMarks() {for (int i=0; i<N; i++) {marks[i] = false;}}
    bool solveQuery(int from, int to);
    bool dfs(bool ispass1, int dest, int parent, int node);
    inline Key makeKey(int from, int to) {return ((((Key)(from)) << 32) | ((Key)(to)));}

    const int N, M, Q;
    AdjList adjList;
    vector<bool> marks;
    unordered_set<int> dfsnodes;
};

PerfectPair::PerfectPair(int n, int m, int q)
: N(n), M(m), Q(q),
  adjList(N, Bucket()),
  marks(N, false),
  dfsnodes() {
    for (int mi=0; mi<M; mi++) {
        int u, v; std::cin >> u >> v;
         u -= 1; v -= 1; //make 0-indexed
         adjList[u].insert(v);
         adjList[v].insert(u);
    }
}

//search for dest
bool PerfectPair::dfs(bool ispass1, int dest, int parent, int node) {
    if (marks[node]) {
        return false;
    }

    marks[node] = true;
    if (parent != -1 && node != dest && ispass1) {
        dfsnodes.insert(node);
    }

    if (node == dest) {
        return true;
    }

    for (const int& neigh : adjList[node]) {
        if (neigh == parent) continue;
        if (!ispass1 && dfsnodes.find(neigh) != dfsnodes.end()) continue;
        if (dfs(ispass1, dest, node, neigh)) return true;
    }

    marks[node] = false;
    if (ispass1 && node != dest && parent != -1) dfsnodes.erase(node);

    return false;
}

bool PerfectPair::solveQuery(int from, int to) {
    //std::cout << "checking " << from <<   " to " << to << std::endl;
    clearMarks();
    dfsnodes.clear();

    if (adjList[from].find(to) != adjList[from].end()) { //direct path exists
        adjList[from].erase(to);
        adjList[to].erase(from);
        bool retval = dfs(true, to, -1, from);
        adjList[from].insert(to);
        adjList[to].insert(from);
        return retval;
    }

    //first dfs
    bool found = dfs(true, to, -1, from);
    if (!found) return false;

    clearMarks();

    //second dfs
    found = dfs(false, to, -1, from);
    return found;
}

void PerfectPair::solve() {
    for (int qi=0; qi<Q; qi++) {
        int from, to; std::cin >> from >> to;
        from -= 1; to -= 1; //make 0-indexed

        bool ans = solveQuery(from, to);
        std::cout << (ans ? "YES" : "NO") << std::endl;
    }
}

int main() {
    int n, m, q; 
    std::cin >> n >> m >> q;

    PerfectPair pp(n, m, q);
    pp.solve();
}


