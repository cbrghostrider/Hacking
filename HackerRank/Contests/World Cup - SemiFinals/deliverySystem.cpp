// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using std::queue;
using std::unordered_map;
using std::pair;
using std::make_pair;
using std::vector;
using std::unordered_set;
using std::map;

typedef unordered_set<int> Bucket;
typedef vector<Bucket> AdjList;

class Kosaraju {
public:
    Kosaraju(int n, int m, int k);
    void runKosaraju();
private:
    enum PassType {PASS1, PASS2};

    void readInput();
    void clearMarks();
    void dfs(int start);
    void dfsLoop();
    bool possibleBFS(int node, int find);
    bool considerLeader(int lead);

    const int N, M, K;
    AdjList graph;
    AdjList revgraph;
    PassType pass;
    vector<bool> marks;
    int time = 0;
    int source = 0;
    vector<pair<int, int>> times;  //(node name, finish time)
    vector<int> leaders;
    unordered_set<int> cities;
    vector<int> leaderNodes;
    unordered_map<int, vector<int>> leaderCities;
};

Kosaraju::Kosaraju(int n, int m, int k)
: N(n), M(m), K(k), 
  graph(N, Bucket()), revgraph(N, Bucket()), 
  pass(PASS1), marks(N, false), time(0), source(0), 
  times(N, make_pair(0, 0)), leaders(N, 0),
  cities(),
  leaderCities() {
    readInput();
}

void Kosaraju::readInput() {
    for (int k=0; k<K; k++) {
        int city; std::cin >> city;
        city -= 1; //0-indexed
        cities.insert(city);
    }
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
                leaderCities.insert(make_pair(source, vector<int>()));
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
        leaderCities[source].push_back(node);
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

bool Kosaraju::possibleBFS(int node, int find) {
    vector<bool> mymarks(N, false);
    queue<int> bfsqu;

    bfsqu.push(node);
    while (!bfsqu.empty()) {
        int check = bfsqu.front(); 
        bfsqu.pop();
        if (check == find) return true;
        mymarks[check] = true;
        for (const int& neigh : graph[check]) {
            if (mymarks[neigh]) continue;
            bfsqu.push(neigh);
        }
    }
    return false;
}

bool Kosaraju::considerLeader(int lead) {
    for (const int& mycity : leaderCities[lead]) {
        if (cities.find(mycity) != cities.end()) return true;
    }
    return false;
}

void Kosaraju::runKosaraju() {
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
    vector<int> order;
    int index = 0;
    int lastLead = 0;
    for (; index < leaderNodes.size(); index++) {
        if (! (considerLeader(leaderNodes[index]))) {
            continue;
        } else {
            lastLead = leaderNodes[index];
            break;
        }
    }
    bool firstTime = true;
    for (; index<leaderNodes.size(); index++) {
        int myleader = leaderNodes[index];
        if (!(considerLeader(myleader)))  continue;

        if (!firstTime) {
            if (!(possibleBFS(lastLead, myleader))) {
                std::cout << -1 << std::endl;
                return;
            }
        }
        firstTime = false;
        lastLead = myleader;

        std::sort(leaderCities[myleader].begin(), leaderCities[myleader].end());
        for (const int& mycity : leaderCities[myleader]) {
            if (cities.find(mycity) != cities.end()) {
                order.push_back(mycity+1);
            }
        }
    }
    for (int i=0; i<order.size(); i++) {
        std::cout << order[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int tcases; std::cin >> tcases;
    for (int t=0; t<tcases; t++) {
        int nval, mval, kval;
        std::cin >> nval >> mval >> kval;
        Kosaraju kosaraju(nval, mval, kval);
        kosaraju.runKosaraju();
    }
}
