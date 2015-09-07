// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <assert.h>
#include <functional>
#include <string>

using std::hash;
using std::unordered_map;
using std::unordered_set;
using std::pair;
using std::make_pair;
using std::vector;
using std::string;

typedef unsigned long long Ways;
const Ways MODNUM = 1000000007;
const int PTLIMIT = 3000;

////////////////////////////////////////////////////////////////////////////////////////////////////
//                            nCr class dynamic programming
////////////////////////////////////////////////////////////////////////////////////////////////////

class PascalsTriangle {
private:
    vector<vector<unsigned long long>> pt;
public:
    PascalsTriangle(int n);
    unsigned long long choose(int n, int k);
};

PascalsTriangle::PascalsTriangle(int n) 
: pt(vector<vector<unsigned long long>>(n+1, vector<unsigned long long>(n+1, 1))) { //init [n+1][n+1] matrix to 1s
    for (int row=2; row<=n; row++) {
        for (int col=1; col<row; col++) {
            pt[row][col] = pt[row-1][col-1] + pt[row-1][col];
            pt[row][col] %= (unsigned long long) MODNUM;
        }
    }
}

unsigned long long PascalsTriangle::choose(int n, int k) {
    if (n <= k || k == 0) return 1;
    return pt[n][k];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                            Memoize some results for use between test cases
////////////////////////////////////////////////////////////////////////////////////////////////////

PascalsTriangle pt(PTLIMIT);
int tidctr=0;
vector<string> strees;                 //mapping from TID -> STree (serialized tree)
unordered_map<string, int> streeToTid; //mapping from STree -> TID
unordered_map<int, Ways> wayCounts;    //mapping from TID to Ways

////////////////////////////////////////////////////////////////////////////////////////////////////
//                            TreeNode class
////////////////////////////////////////////////////////////////////////////////////////////////////

struct TreeNode {
    const int N;
    int id;                              //this is NOT value, nor TID
    vector<TreeNode*> neighbors;         //all the neighbors I have
    unordered_map<TreeNode*, int> sizes; //size of subtree that is rooted at *this* TreeNode, with parent as key
    unordered_map<TreeNode*, int> tids;  //tid of subtree that is rooted at *this* TreeNode, with parent as key

    TreeNode(int n, int iden) : N(n), id(iden), neighbors(), sizes(), tids() {}
    void addNeighbor(TreeNode* neigh);
    void initialize(TreeNode* parent);

    int findSize(TreeNode* parent);
    string findSTree(TreeNode* parent);
};

void TreeNode::addNeighbor(TreeNode* neigh) {
    neighbors.push_back(neigh);
}

//sets the strees, tids, and sizes appropriately
void TreeNode::initialize(TreeNode* parent) {
    if (sizes.find(parent) != sizes.end()) {
        return; //already processed in this direction previously
    }

    //dfs initialize
    for (TreeNode* node : neighbors) {
        if (node == parent) continue;
        node->initialize(this);
    }

    int totalsize = 1; //for myself
    int childctr=0;
    vector<TreeNode*> childs;
    vector<string> childtrees;
    string streeP = "(*"; //start of tree, and its root
    for (TreeNode* node : neighbors) { 
        if (node == parent) continue;
        childctr++;

        //find child size
        int csize = node->findSize(this);
        totalsize += csize;
        childs.push_back(node);

        //and child stree
        string ctree = node->findSTree(this);
        childtrees.push_back(ctree);
        //streeP += ctree;
    }

    //sort ctrees, so that result is properly topologized
    std::sort(childtrees.begin(), childtrees.end());

    for (string& ctree : childtrees) {
        streeP += ctree;
    }
    for (; childctr<2; childctr++) {
        streeP += "()"; //add NULL
    }
    streeP += ")"; //add end of tree

    auto cit = streeToTid.find(streeP);
    int ptid;
    if (cit == streeToTid.end()) { //doesn't exist yet
        strees.push_back(streeP);
        streeToTid.insert(make_pair(streeP, tidctr));
        ptid = tidctr;
        tidctr++;
    } else {
        ptid = cit->second;
    }

    sizes.insert(make_pair(parent, totalsize));
    tids.insert(make_pair(parent, ptid));

    //set the ways for this subtree, coming from parent

    auto wayit = wayCounts.find(ptid);
    if (wayit != wayCounts.end()) {
        return; //already computed
    }
    if (childs.size() == 0) {
        wayCounts.insert(make_pair(ptid, 1)); //only 1 way to do this
        return;
    }
    if (childs.size() == 1) {
        assert(childs[0]->tids.find(this) != childs[0]->tids.end());
        auto cwayit = wayCounts.find(childs[0]->tids[this]);
        Ways newways = cwayit->second * 2;
        newways %= MODNUM;
        wayCounts.insert(make_pair(ptid, newways));
        return;
    }

    //two children
    assert(childs[0]->tids.find(this) != childs[0]->tids.end());
    auto cway0it = wayCounts.find(childs[0]->tids[this]);
    int size0 = childs[0]->findSize(this);
    assert(childs[1]->tids.find(this) != childs[1]->tids.end());
    auto cway1it = wayCounts.find(childs[1]->tids[this]);
    int size1 = childs[1]->findSize(this);

    Ways newways = cway0it->second * cway1it->second;
    newways %= MODNUM;
    newways *= pt.choose((size0+size1), size0); 
    newways %= MODNUM;
    if (size0 != size1) {
        newways *= 2;
        newways %= MODNUM;
    }
    wayCounts.insert(make_pair(ptid, newways));
}

//Size of subtree rooted at this TreeNode, with parent passed in
int TreeNode::findSize(TreeNode* parent) {
    auto it = sizes.find(parent);
    assert(it != sizes.end());
    return (it->second);
}

string TreeNode::findSTree(TreeNode* parent) {
    auto it = tids.find(parent);
    assert(it != tids.end());
    return (strees[it->second]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                            Reflections class
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef vector<TreeNode*> Graph;

class Reflections {
public:
    Reflections(int n);
    ~Reflections();
    Ways countWays();
private:
    void readInput();
    void initialize();
    const int N;
    Graph graph;
};

Reflections::Reflections(int n) 
: N(n), graph() {
    for (int i=0; i<N; i++) {
        graph.push_back(new TreeNode(N, i));
    }
    readInput();
    initialize();
}

Reflections::~Reflections() {
    for (int i=0; i<N; i++) {
        delete graph[i];
    }
}

void Reflections::readInput() {
    for (int i=0; i<N-1; i++) {
        int x, y; std::cin >> x >> y;
        x -= 1; y -= 1;
        graph[x]->addNeighbor(graph[y]);
        graph[y]->addNeighbor(graph[x]);
    }
}

void Reflections::initialize() {
    for (int i=0; i<N; i++) {
        if (graph[i]->neighbors.size() <= 2) {
            graph[i]->initialize(NULL);
        }
    }
}

Ways Reflections::countWays() {
    Ways total = 0;
    unordered_set<int> seen;
    for (TreeNode* root : graph) {
        if (root->neighbors.size() == 3) continue;
        //std::cout << "Checking tree: " << root->findSTree(NULL) << std::endl;
        int rtid = root->tids[NULL];
        if (seen.find(rtid) != seen.end()) continue; //already processed this topology
        
        seen.insert(rtid);
        auto wit = wayCounts.find(rtid);
        assert(wit != wayCounts.end());

        Ways theseWays = wit->second;
        //std::cout << "Adding " << theseWays << std::endl;
        //std::cout << "Root id: " << root->id << "; ways = " << theseWays << std::endl;
        total += theseWays;
        total %= MODNUM;
    }
    return total;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                            main driver
////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        int n; std::cin >> n;
        Reflections ref(n);
        Ways ans = ref.countWays();
        std::cout << ans << std::endl;
    }
}



