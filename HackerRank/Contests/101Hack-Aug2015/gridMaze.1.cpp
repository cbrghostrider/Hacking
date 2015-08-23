// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// I did not have time to attempt this problem during the contest. 
// However, I had a pretty good idea on how it needed to be solved. 
// I wrote this code after the contest. 
// Currently, there is a known issue, which causes the code to fail on 7/23 tests.
// But it passes the other 16/23 tests.
// Please check out my blog on cbrghostrider.wordpress.com for more details on this.
//
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <string>

using std::string;
using std::make_pair;
using std::pair;
using std::unordered_map;
using std::priority_queue;
using std::vector;

//the cost for moving from empty cell to another empty cell
//or from wall to empty cell
#define EMPTYCOST (1)

typedef long long Node;
typedef long long Weight;

struct Edge {
    Weight wt;
    Node from;
    Node to;
    Edge (Weight w, Node fnd, Node tond) : wt(w), from(fnd), to(tond) {}
};

struct Coord {
    int row; 
    int col;
    Coord (int r, int c) : row(r), col(c) {}
    bool operator==(const Coord& rhs) const {return (rhs.row == row && rhs.col == col);}
};

typedef vector<vector<Edge>> AdjList;
typedef pair<Weight, Edge> QuElem;

struct HeapCmp {
    bool operator() (const QuElem& lhs, const QuElem& rhs) {
        return (lhs.first > rhs.first);
    }
};

typedef priority_queue<QuElem, vector<QuElem>, HeapCmp> DjMinHeap;

class GridMaze {
public:
    GridMaze();
    int minWallBreakdowns();
private:
    
    //utility functions
    Node makeNode(int r, int c);
    Coord getCoord(Node nd);
    Weight wallCost() const;
    int numNodes() const;

    void displayPath(vector<Node>& path);

    //input functions, and computing initial graph
    void readInput();
    void computeGraph();

    //run dijkstras, and compute paths
    vector<Node> shortestPath(Coord src, Coord dst);

    //breaks the walls that need to be broken along path
    void breakWalls(vector<Node>& path);

    int N, M;
    vector<vector<char>> grid;
    AdjList adjList;
    Coord S, P;
    Coord EXIT;
    int broken;
};

GridMaze::GridMaze()
: N(0), M(0), grid(), adjList(), S(0, 0), P(0, 0), EXIT(0, 0), broken(0) {
    readInput();
    computeGraph();
}

Weight GridMaze::wallCost() const {
    return (N*M);
}

int GridMaze::numNodes() const {
    return (N*M + 1);
}

Coord GridMaze::getCoord(Node n) {
    return Coord(n/M, n%M);
}

Node GridMaze::makeNode(int r, int c) {
    return (r*M + c);
}

void GridMaze::readInput() {
    std::cin >> N >> M;
    grid = vector<vector<char>>(N, vector<char>(M, '.'));
    for (int r=0; r<N; r++) {
        string str; std::cin >> str;
        for (int c=0; c<M; c++) {
            grid[r][c] = str[c];
            if (grid[r][c] == 'S') S = Coord(r, c);
            if (grid[r][c] == 'P') P = Coord(r, c);
        }
    }
}

void GridMaze::computeGraph() {
    adjList = vector<vector<Edge>>(numNodes(), vector<Edge>());
    EXIT = Coord(N, 0);
    for (int r=0; r<N; r++) {
        for (int c=0; c<M; c++) {
            if (r != 0)   { 
                Weight edgeWt = grid[r-1][c] == '#' ? wallCost() : EMPTYCOST;
                adjList[makeNode(r, c)].push_back(Edge(edgeWt, makeNode(r, c), makeNode(r-1, c)));
            }
            if (r != N-1) { 
                Weight edgeWt = grid[r+1][c] == '#' ? wallCost() : EMPTYCOST;
                adjList[makeNode(r, c)].push_back(Edge(edgeWt, makeNode(r, c), makeNode(r+1, c)));
            }
            if (c != 0)   { 
                Weight edgeWt = grid[r][c-1] == '#' ? wallCost() : EMPTYCOST;
                adjList[makeNode(r, c)].push_back(Edge(edgeWt, makeNode(r, c), makeNode(r, c-1)));
            }
            if (c != M-1) { 
                Weight edgeWt = grid[r][c+1] == '#' ? wallCost() : EMPTYCOST;
                adjList[makeNode(r, c)].push_back(Edge(edgeWt, makeNode(r, c), makeNode(r, c+1)));
            }
            if (r == 0 || c == 0 || r == N-1 || c == M-1) { //if on the edge, connect to exit
                adjList[makeNode(r, c)].push_back(Edge(0, makeNode(r, c), makeNode(EXIT.row, EXIT.col)));
            }
        }
    }
}

vector<Node> GridMaze::shortestPath(Coord src, Coord dst) {
    unordered_map<Node, Node> ancestors;
    Node source = makeNode(src.row, src.col);
    Node destination = makeNode(dst.row, dst.col);

    DjMinHeap mheap;
    mheap.push(make_pair(0, Edge(0, source, source)));

    while (!mheap.empty()) {
        QuElem melem = mheap.top(); mheap.pop();
        Edge myEdge = melem.second;
        Node me = myEdge.from;
        Node towards = myEdge.to;
        Weight sofar = melem.first;

        if (ancestors.find(towards) != ancestors.end()) continue;
        ancestors.insert(make_pair(towards, me)); //got to towards from me

        if (towards == destination) break;

        for (const Edge& e : adjList[towards]) {
            if (ancestors.find(e.to) != ancestors.end()) continue;
            mheap.push(make_pair(sofar + e.wt, e));
        }
    }

    auto it = ancestors.find(destination);
    if (it == ancestors.end()) { //not connected to the destination
        return vector<Node>();
    }

    vector<Node> path;

    while (destination != source) {
        path.push_back(destination);
        destination = ancestors.find(destination)->second;
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());
    return path;
}

void GridMaze::displayPath(vector<Node>& path) {
    for (Node& nd : path) {
       Coord crd = getCoord(nd);
      std::cout << "(" << crd.row << ", " << crd.col << ") -> ";
    }
    std::cout << std::endl;
}

void GridMaze::breakWalls(vector<Node>& path) {
    for (Node& nd : path) {
        Coord ncrd = getCoord(nd);
        if (ncrd == EXIT) continue;
        if (grid[ncrd.row][ncrd.col] != '#') continue;

        //break this wall
        broken++;
        grid[ncrd.row][ncrd.col] = '.';

        //std::cout << "Breaking wall at: (" << ncrd.row << ", " << ncrd.col << ")" << std::endl;

        //and repair the graph
        vector<Node> fromNodes;
        if (ncrd.row != 0) {
            Node top = makeNode(ncrd.row-1, ncrd.col);
            fromNodes.push_back(top);
        }
        if (ncrd.row != N-1) { 
            Node bottom = makeNode(ncrd.row+1, ncrd.col);
            fromNodes.push_back(bottom);
        }
        if (ncrd.col != 0) {
            Node left = makeNode(ncrd.row, ncrd.col-1);
            fromNodes.push_back(left);
        }
        if (ncrd.col != M-1) {
            Node right = makeNode(ncrd.row, ncrd.col+1);
            fromNodes.push_back(right);
        }

        for (Node& fn : fromNodes) {
            for (Edge& e : adjList[fn]) {
                if (e.to == nd) {
                    e.wt = EMPTYCOST;
                    break;
                }
            }
        }
    }
}

int GridMaze::minWallBreakdowns() {
    vector<Node> pathSP = shortestPath(S, P);
    //displayPath(pathSP);

    breakWalls(pathSP); 

    vector<Node> pathPE = shortestPath(P, EXIT);
    //displayPath(pathPE);

    breakWalls(pathPE);

    return broken;
}

int main() {
    GridMaze gm;
    int ans = gm.minWallBreakdowns();
    std::cout << ans << std::endl;
}

