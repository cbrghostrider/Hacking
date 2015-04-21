#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <tuple>
#include <fstream>
#include <limits>

//primitive obsession? 
typedef unsigned int                   Node;
typedef long                           Weight;
typedef std::tuple<Node, Node, Weight> Edge;
typedef std::vector<Edge>              AdjBucket;
typedef std::vector<AdjBucket>         AdjList;

void readGraph (AdjList& adjl, const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file " << filename << " for reading" << std::endl;
    }

    unsigned int numNodes, numEdges;
    file >> numNodes >> numEdges;
    adjl.reserve(numNodes);

    for (Node n=0; n < numNodes; n++) {
        adjl.emplace_back(AdjBucket());
    }

    for (unsigned int i=0; i<numEdges; i++) {
        Node from, to;
        Weight w;
        file >> from >> to >> w;
        Node adj_from = from-1, adj_to = to-1; //renaming nodes to be 0 indexed
        adjl[adj_from].emplace_back(Edge(adj_from, adj_to, w));
    }

    file.close();
}

bool checkNegativeCycle (Weight const *const *const pwt, unsigned int size) 
{
    for (unsigned int i=0; i < size; i++) {
        if (pwt[i][i] < 0) {
            return true;
        }
    }
    return false;
}

// sets is_possible to whether path exists; set to false if negative cycle
// sets pathWt to value of shortest shortest path
void computeShortestShortestPath (const AdjList& adjl, Weight& pWt, bool& is_possible)
{
    Weight **pathWt;
    pathWt = new Weight*[adjl.size()];
    for (unsigned int i=0; i<adjl.size(); i++) {
        pathWt[i] = new Weight[adjl.size()];
    }

    //init step for floyd warshall
    for (Node i=0; i<adjl.size(); i++) {
        for (Node j=0; j<adjl.size(); j++) {
            auto it = std::find_if(adjl[i].begin(), adjl[i].end(), [&i, &j] (const Edge& e) -> bool {
                return (std::get<0>(e) == i && std::get<1>(e) == j);
            });
            if (i == j) {
                pathWt[i][j] = 0;                // self-to-self:     0 cost
            } else if (it != adjl[i].end()) {
                pathWt[i][j] = std::get<2>(*it); // self-to-neighbor: edge weight cost
            } else {
                pathWt[i][j] = std::numeric_limits<Weight>::max(); 
            }
        }
    }

    //main floyd warshall algorithm
    for (Node k=0; k < adjl.size(); k++) {
        for (Node i=0; i < adjl.size(); i++) {
            for (Node j=0; j < adjl.size(); j++) {
                Weight infinity = std::numeric_limits<Weight>::max();
                Weight cmpMe;
                if (pathWt[i][k] == infinity || pathWt[k][j] == infinity) {
                    cmpMe = infinity;
                } else {
                    cmpMe = pathWt[i][k] + pathWt[k][j];
                }
                if (cmpMe < pathWt[i][j]) {
                    pathWt[i][j] = cmpMe;
                }
            }
        }
    }

    Weight min = std::numeric_limits<Weight>::max();
    for (Node i=0; i < adjl.size(); i++) {
        for (Node j=0; j < adjl.size(); j++) {
            if (pathWt[i][j] < min) {
                min = pathWt[i][j];
            } 
        }
    }

    if (checkNegativeCycle(pathWt, adjl.size())) {
        //negative cycle
        is_possible = false;
        pWt = std::numeric_limits<Weight>::max();
    } else {
        is_possible = true;
        pWt = min;
    }

    for (unsigned int i=0; i<adjl.size(); i++) {
        delete [] pathWt[i];
    }
    delete [] pathWt;
}

int main (int argc, char *argv[])
{
    //if (argc < 4) {
    //    std::cout << "Not passing enough arguments: Need 3 graphs" <<  std::endl;
    //    exit(1);
    //}

    AdjList l1, l2, l3;
    if (argc >= 2) readGraph(l1, argv[1]);
    if (argc >= 3) readGraph(l2, argv[2]);
    if (argc >= 4) readGraph(l3, argv[3]);

    Weight w1, w2, w3;
    w1 = w2 = w3 = std::numeric_limits<Weight>::max();
    bool   p1 = false, p2 = false, p3 = false;
    if (argc >= 2) computeShortestShortestPath(l1, w1, p1);
    if (argc >= 3) computeShortestShortestPath(l2, w2, p2);
    if (argc >= 4) computeShortestShortestPath(l3, w3, p3);

    if (p1 == false && p2 == false && p3 == false) {
        std::cout << "All graphs have negative cost cycles" << std::endl;
    } else {
        Weight m12 = w1  < w2 ? w1  : w2;
        Weight mm3 = m12 < w3 ? m12 : w3;
        std::cout << "Min shortest shortest path=" << mm3 << std::endl;
    }
}

