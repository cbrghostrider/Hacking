// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using std::unordered_set;
using std::unordered_map;
using std::queue;
using std::pair;
using std::make_pair;
using std::vector;

#define MIN_ROLL  (1)
#define MAX_ROLL  (6)
#define NUM_NODES (100)
#define END_NODE  (NUM_NODES-1)

class SnakesAndLadders {
    vector<unordered_set<int> > adjList;    //normal adjacency list
    vector<unordered_set<int> > revAdjList; //adj list for reversed arrows
    unordered_map<int, int> ladders;        
    unordered_map<int, int> snakes;       
private:
    void readInput();
    void repairGraph(unordered_map<int, int>& connects);
public:
    SnakesAndLadders();
    int bfs();
};

SnakesAndLadders::SnakesAndLadders() 
: adjList(NUM_NODES, unordered_set<int>()), revAdjList(NUM_NODES, unordered_set<int>()), ladders(), snakes() {

    //make mandatory connections for the rolls [1, 6] at that cell
    for (int i=0; i<NUM_NODES; i++) {
        for (int roll=MIN_ROLL; roll<=MAX_ROLL; roll++) {
            if (roll + i < NUM_NODES) {
                adjList[i].insert(i+roll); //directed edge from (i) to (i+roll)
                revAdjList[i+roll].insert(i); //reverse edge
            }
        }
    }

    //connect up the connections between snakes and ladders
    readInput();

    //connect up the snakes/ladders
    repairGraph(ladders);
    repairGraph(snakes);
}

void SnakesAndLadders::readInput() {
    int n, m;
    std::cin >> n;
    for (int i=0; i<n; i++) {
        int st, end;
        std::cin >> st >> end;
        ladders.insert(make_pair(st-1, end-1)); //0-indexed
    }
    std::cin >> m;
    for (int i=0; i<m; i++) {
        int st, end;
        std::cin >> st >> end;
        snakes.insert(make_pair(st-1, end-1)); //0-indexed
    }
}

// note snakes/ladders do not begin/end at same location w.r.t. each other, 
// this makes it much easier!
void SnakesAndLadders::repairGraph(unordered_map<int, int>& connects) {
    for (auto connect : connects) {
        int stp = connect.first;
        int endp = connect.second;

        //now all the guys that are incoming to stp, will go to endp instead
        for (const int& src : revAdjList[stp]) {
            adjList[src].erase(stp);
            adjList[src].insert(endp);
        }

        adjList[stp].clear(); //remove previous choices
        revAdjList[stp].clear(); //remove previous choices
    }
}

int SnakesAndLadders::bfs() {
    vector<bool> visited(NUM_NODES, false);

    queue<pair<int, int>> bfsqueue;
    bfsqueue.push(make_pair(0, 0)); //node 0, distance to it is 0

    while (!bfsqueue.empty()) {
        auto head = bfsqueue.front(); bfsqueue.pop();
        int cost = head.first;
        int me   = head.second;
        visited[me] = true;
        if (me == END_NODE) return cost;

        for (const int& neighbor : adjList[me]) {
            if (visited[neighbor]) continue;
            bfsqueue.push(make_pair(cost+1, neighbor));
        }
    }

    return -1; //no path
}


int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        SnakesAndLadders sal;
        int ans = sal.bfs();
        std::cout << ans << std::endl;
    }
}


