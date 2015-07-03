// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// Functionally correct but algorithmically a bit inefficient (perhaps)
// Currently 6/7 test cases pass, 1/7 time out
// Of course, the last data set is HUGE, and getting it to run under 1s will be very challenging
//
// this algorithm starts with the startnode, with current path len set to 1
// I perform a process of discovery, by seeing which nodes are not connected to my beginning set
// these can be reached in current path len hops
//
// then I add the newly reached nodes in the beginning set, and remove the processed nodes from it
// the discovery process continues, until all nodes have lengths marked
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using std::set;
using std::vector;

class RustMurderer {
public:
    RustMurderer();
    void printShortestVillagePaths();
private:
    void readInput();
    int startNode;
    vector<set<int>> adjList;
};

RustMurderer::RustMurderer() 
: startNode(0), adjList() {
    readInput();
}

void RustMurderer::readInput() {
    int n, m; std::cin >> n >> m;

    adjList = vector<set<int>>(n, set<int>());
    for (int i=0; i<m; i++) {
        int n1, n2; std::cin >> n1 >> n2;
        adjList[n1-1].insert(n2-1); //make 0-indexed
        adjList[n2-1].insert(n1-1); //make 0-indexed
    }

    std::cin >> startNode; startNode -= 1; //make 0 indexed
}

void RustMurderer::printShortestVillagePaths() {
    int clen = 1;                            //the current length I will write
    vector<int> plengths(adjList.size(), 0); //I will write the lengths here

    set<int> leftovernodes; for (int i=0; i<adjList.size(); i++) leftovernodes.insert(i);
    leftovernodes.erase(startNode);

    set<int> newnodes, foundnodes; 
    foundnodes.insert(startNode);

    while (leftovernodes.size()) {
        newnodes = foundnodes; 
        foundnodes.clear();

        while (!newnodes.empty()) {
            const int& nn = *(newnodes.begin());
            newnodes.erase(nn);
            std::set_difference(leftovernodes.begin(), leftovernodes.end(), adjList[nn].begin(), adjList[nn].end(), std::inserter(foundnodes, foundnodes.end()));
        }

        for (const int& found : foundnodes) {
            plengths[found] = clen;
            leftovernodes.erase(found);
        }

        clen++;
    }

    for (int nd = 0; nd < adjList.size(); nd++) {
        if (nd == startNode) continue;
        std::cout << plengths[nd] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i < tc; i++) {
        RustMurderer rm;
        rm.printShortestVillagePaths();
    }
}
