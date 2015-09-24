// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;

typedef int Node;
typedef long long Weight;

struct Edge {
    Node from; 
    Node to;
    Weight wt;
    Edge(Node f, Node t, Weight w) : from(f), to(t), wt(w) {}
};

typedef vector<Edge> Bucket;
typedef vector<Bucket> AdjList;

class WorldCup {
public:
    WorldCup(int n, int t);
    ~WorldCup();
    void playTasks();
private:
    void dfs(Node from, Node parent, Node origin, Weight wtsofar);
    void computeDists();
    void sumDistances(vector<Node>& nset);
    const int N, T;
    AdjList adjList;
    Weight **wt;
};

WorldCup::WorldCup(int n, int t)
: N(n), T(t),
  adjList(N, Bucket()) {
      //allocate memory 
      wt = new Weight*[N];
      for (int i=0; i<N; i++) {
          wt[i] = new Weight[N];
      }
      
      for (int i=0; i<N; i++) {
          for (int j=0; j<N; j++) {
              wt[i][j] = -1;
          }
      }

      for (int i=0; i<N-1; i++) {
          Node from, to; std::cin >> from >> to;
          from -= 1; to -= 1; //0-indexed
          Weight wt; std::cin >> wt;
          adjList[from].push_back(Edge(from, to, wt));
          adjList[to].push_back(Edge(to, from, wt));
      }
}

WorldCup::~WorldCup() {
    for (int i=0; i<N; i++) {
        delete [] wt[i];
    }
    delete [] wt;
}

void WorldCup::dfs(Node from, Node parent, Node origin, Weight wtsofar) {
    if (wt[origin][from] == -1) { wt[origin][from] = wtsofar;}
    if (wt[from][origin] == -1) { wt[from][origin] = wtsofar;}

    for (const Edge& edg : adjList[from]) {
        Node neigh = edg.to;
        Weight wt = edg.wt;
        if (neigh == parent) continue;
        dfs(neigh, from, origin, wtsofar+wt);
    }
}

void WorldCup::computeDists() {
    for (Node ori=0; ori<N; ori++) {
        dfs(ori, -1, ori, 0);
    }
}

void WorldCup::sumDistances(vector<Node>& nset) {
    Weight total = 0;
    for (int f=0; f<nset.size(); f++) {
        for (int t=f+1; t<nset.size(); t++) {
            if (wt[nset[f]][nset[t]] == -1) { dfs(nset[f], -1, nset[f], 0);}
            //std::cout << "Distance from " << (nset[f]) << " to " << nset[t] << " = " << wt[nset[f]][nset[t]] << std::endl;       
            total += wt[nset[f]][nset[t]];
        }
    }
    std::cout << total << std::endl;
}

void WorldCup::playTasks() {
    //computeDists();

    for (int t=0; t<T; t++) {
        int k; std::cin >> k;
        vector<Node> nset(k, 0);
        for (int i=0; i<k; i++) {
            std::cin >> nset[i];
            nset[i] -= 1;
        }
        sumDistances(nset);
    }
}

int main() {
    int n, t; std::cin >> n >> t;
    WorldCup wc(n, t);
    wc.playTasks();
}

