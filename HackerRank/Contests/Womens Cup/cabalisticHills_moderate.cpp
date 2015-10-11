// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//detect eulerian cycle
#include <iostream>
#include <cstdio>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <string>

using std::string;
using std::queue;
using std::unordered_map;
using std::pair;
using std::make_pair;
using std::vector;
using std::unordered_multiset;
using std::map;

string failMessage("Danger!! Lucifer will trap you");
string passMessage("Go on get the Magical Lamp");

typedef unordered_multiset<int> Bucket;
typedef vector<Bucket> AdjList;

class Kosaraju {
public:
    Kosaraju(int n, int m);
    bool runKosaraju();
private:
    enum PassType {PASS1, PASS2};

    void readInput();
    void clearMarks();
    void dfs(int start);
    void dfsLoop();

    const int N, M;
    AdjList graph;
    AdjList revgraph;
    PassType pass;
    vector<bool> marks;
    int time = 0;
    int source = 0;
    vector<pair<int, int>> times;  //(node name, finish time)
    vector<int> leaders;
    vector<int> leaderNodes;
};

Kosaraju::Kosaraju(int n, int m)
: N(n), M(m), 
  graph(N, Bucket()), revgraph(N, Bucket()), 
  pass(PASS1), marks(N, false), time(0), source(0), 
  times(N, make_pair(0, 0)), leaders(N, 0),
  leaderNodes() {
    readInput();
}

void Kosaraju::readInput() {
    int from, to;
    for (int m=0; m<M; m++) {
        std::cin >> from >> to;
        from -= 1; to -= 1; //make 0-indexed
        graph[from].insert(to);
        revgraph[to].insert(from);
    }
    for (int i=0; i<N; i++) {
        times[i] = make_pair(i, 0);
    }
}

void Kosaraju::clearMarks() {
    for (int i=0; i<N; i++) {
        marks[i] = false;
    }
}

void Kosaraju::dfsLoop() {
    for (int ti=0; ti<times.size(); ti++) {
        int node = times[ti].first;
        if (marks[node] == false) {
            if (pass == PASS2) {
                source = node;
                leaderNodes.push_back(source);
            }
            dfs(node);
        }
    }
}

void Kosaraju::dfs(int node) {
    marks[node] = true;

    if (pass == PASS2) {
        leaders[node] = source;
    }

    const Bucket& mybucket = ((pass == PASS2) ? revgraph[node] : graph[node]);
    for (const int& neigh : mybucket) {
        if (marks[neigh] == false) {
            dfs(neigh);
        }
    }

    if (pass == PASS1) {
        time++;
        times[node].second = time;
    }
}


bool Kosaraju::runKosaraju() {
    //run pass 1 of Kosaraju (reverse DFS)
    pass = PASS1;
    dfsLoop();

    //clear bookkeeping and prep for pass 2
    clearMarks();
    std::sort(times.begin(), times.end(), [] (const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
        return (lhs.second > rhs.second);
    });

    //run pass 2 of kosaraju
    pass = PASS2;
    dfsLoop();

    //compute the answers needed
    int startNode = 0;
    int endNode = N-1;

    //start and end node must belong to same strongly connected component
    int sccLead = leaders[startNode];
    if (sccLead != leaders[endNode]) {
        return false;
    }

    //all other SCCs must have 1 size i.e. no edges in and out of them
    for (const int& lead : leaderNodes) {
        if (lead == sccLead) continue;
        if (graph[lead].size() > 0 || revgraph[lead].size() > 0) {
            return false;
        }
    }

    //all nodes must have same in and out degree, and this must be even
    for (int node=0; node<N; node++) {
        int indeg = revgraph[node].size();
        int outdeg = graph[node].size();

        if (indeg != outdeg) return false;
    }

    return true;
}

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        int n, m; std::cin >> n >> m;
        Kosaraju kosaraju(n, m);
        bool ans = kosaraju.runKosaraju();
        if (ans) {
            std::cout << passMessage << std::endl;
        } else {
            std::cout << failMessage << std::endl;
        }
    }
}
