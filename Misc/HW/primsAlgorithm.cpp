#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <utility>
#include <list>
#include <algorithm>

//#include "boost/graph/graph_traits.hpp"
//#include "boost/graph/adjacency_list.hpp"

class AdjacencyList {
  public:
    typedef unsigned int t_vert;
    typedef int t_edge_w;

    AdjacencyList();
    ~AdjacencyList();

    void addVertex(); //add next vertex 
    void addEdge(t_vert p1, t_vert p2, t_edge_w wt);

    void display();
    void runPrimsAlg();

    long long mstValue();
  private:
    typedef std::pair<t_vert, t_edge_w> t_edge;
    typedef std::list<t_edge> t_adj_list_elem;
    typedef std::vector<t_adj_list_elem> t_adj_list;

    void markVertex(const t_vert vert); //mark vert as visited
    void clearVertex(const t_vert vert);//mark vert as not visited
    void clearMarks(); //clears visited marks on all vertices
    bool finishedPrims();

    t_adj_list adj_list_;
    std::vector<bool> visited_;

    std::list<t_edge> mst_edges_;
    std::list<t_edge> frontier_;
};

long long AdjacencyList::mstValue()
{
    long long val=0;
    for_each(mst_edges_.begin(), mst_edges_.end(), [&val] (const t_edge& edge)-> void {
        val += edge.second;
    });
    return val;
}

bool AdjacencyList::finishedPrims()
{
    bool ret = true;
    for (const bool& bl : visited_) {
        if (bl == false) {
            return false;
        }
    }
    return ret;
}

void AdjacencyList::runPrimsAlg()
{
    //start with v1
    visited_[0]= true;
    frontier_ = adj_list_[0];

    while (!finishedPrims()) {
        /*std::sort(frontier_.begin(), frontier_.end(), [] (const t_edge& lhs, const t_edge& rhs) -> bool {
            return (lhs.second < rhs.second);
        });*/
        frontier_.sort([] (const t_edge& lhs, const t_edge& rhs) -> bool {
            return (lhs.second < rhs.second);
        });

        t_edge add_e = frontier_.front();
        frontier_.pop_front();
        t_vert add_v = add_e.first;

        assert(visited_[add_v] == false);

        mst_edges_.push_back(add_e);
        visited_[add_v] = true;

        //remove those edges from the frontier that end at add_v
        frontier_.remove_if([add_v] (t_edge& edg) ->bool { return edg.first == add_v; });

        //add those edges from add_v that dont end in a finished vertex
        for_each(adj_list_[add_v].begin(), adj_list_[add_v].end(),[this] (t_edge& edge) -> void {
            if (visited_[edge.first] == false) {
                this->frontier_.push_back(edge);
            }
        });
    }
}

AdjacencyList::AdjacencyList()
{
}

AdjacencyList::~AdjacencyList()
{
}

void AdjacencyList::addVertex()
{
    adj_list_.push_back(t_adj_list_elem());
    visited_.push_back(false);
}

void AdjacencyList::addEdge(t_vert p1, t_vert p2, t_edge_w wt)
{
    adj_list_[(p1)].push_back(std::make_pair((p2), wt)); //add to p1's list
    adj_list_[(p2)].push_back(std::make_pair((p1), wt)); //and to p2's list
}

void AdjacencyList::markVertex(const t_vert index)
{
    visited_[index] = true;
}

void AdjacencyList::clearVertex(const t_vert index)
{
    visited_[index] = false;
}

void AdjacencyList::clearMarks()
{
    for (unsigned int i=0; i<visited_.size(); i++) {
        clearVertex(i);
    }
}

void AdjacencyList::display()
{
    unsigned int i = 0;
    for_each(adj_list_.begin(), adj_list_.end(), [&i] (t_adj_list_elem& edges) -> void {
        std::cout << "V" << ++i <<": ";
        for_each(edges.begin(), edges.end(), [] (t_edge& edge)-> void {
            std::cout << "(" << (edge.first + 1) << ", " << edge.second <<") ";
        });
        std::cout << std::endl;
    });
}

void readGraph(AdjacencyList& adj, const char* fileName)
{
    std::string line;
    std::ifstream input(fileName);
    if (input.is_open()) {
        getline(input, line);
        std::stringstream ve(line);
        unsigned int nVertices=0, nEdges=0;
        ve >> nVertices >> nEdges;

        std::cout << "Found " << nVertices << " vertices and " << nEdges << " edges" << std::endl;

        for (unsigned int v=0; v<nVertices; v++) {
            adj.addVertex();
        }

        while (getline(input, line)) {
            std::stringstream ss(line);
            unsigned int v1=0, v2=0;
            int wt=0;
            ss >> v1 >> v2 >> wt;

            adj.addEdge(v1-1, v2-1, wt);
        }
        input.close();
    } else {
        std::cout << "Could not open" << fileName << std::endl;
    }
}



int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage error" << std::endl;
    }

    AdjacencyList adjl;
    readGraph(adjl, argv[1]);

    //adjl.display();

    adjl.runPrimsAlg();
    long long mstval = adjl.mstValue();

    std::cout << "MST value is " << mstval << std::endl;
}


