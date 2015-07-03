// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// currently 2 test cases out of 16 time out
// O(1) insert, 
// O(O(c)) delete (where O(c) is max # of children of any node), 
// O(k) - kth ancestor
// need to possibly optimize the last one further
//
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <utility>

using std::pair;
using std::make_pair;
using std::vector;
using std::unordered_map;

class TreeNode {
public:
    TreeNode(int i) : id(i), parent(nullptr), children() {}
    int id;
    TreeNode* parent;
    vector<TreeNode*> children;
};

class AncestorTree {
public:
    AncestorTree();
    ~AncestorTree();
    void processQuery();
private:
    void readInput();
    void addNode(int child, int parent);
    void removeNode(int node);
    int kthAncestor(int node, int k);

    int numNodes;
    unordered_map<int, TreeNode*> indToNode;
};

AncestorTree::AncestorTree() 
: numNodes(0), indToNode() {
    readInput();
}

AncestorTree::~AncestorTree() {
    for (auto nt : indToNode) {
        delete nt.second;
    }
}

void AncestorTree::readInput() {
    std::cin >> numNodes;
    for (int i=0; i<numNodes; i++) {
        int x, y; std::cin >> x >> y;
        addNode(x, y);
    }
}

void AncestorTree::addNode(int child, int parent) {
    TreeNode *pnode, *cnode;

    auto cit = indToNode.find(child);
    if (cit == indToNode.end()) { //havent' encountered this node yet
        cnode = new TreeNode(child);
        indToNode.insert(make_pair(child, cnode));
    } else {
        cnode = cit->second;
    }

    if (parent == 0) return; //namesake... this child is root

    auto pit = indToNode.find(parent);
    if (pit == indToNode.end()) { //havent' encountered this node yet
        pnode = new TreeNode(parent);
        indToNode.insert(make_pair(parent, pnode));
    } else {
        pnode = pit->second;
    }

    cnode->parent = pnode;
    pnode->children.push_back(cnode);
}

void AncestorTree::removeNode(int node) {
    auto dit = indToNode.find(node);
    if (dit == indToNode.end()) return;

    TreeNode *dnode = dit->second;
    
    //process this node's parent, if it has one
    if (dnode->parent) {
        auto it = std::remove(dnode->parent->children.begin(), dnode->parent->children.end(), dnode);
        dnode->parent->children.erase(it, dnode->parent->children.end());
    }

    //process each of this node's children, if it has any
    for (TreeNode*& child : dnode->children) {
        if (child->parent == dnode) child->parent = nullptr;
    }

    //remove this node
    delete dnode;
    indToNode.erase(dit);
}

int AncestorTree::kthAncestor(int node, int k) {
    auto nit = indToNode.find(node);
    if (nit == indToNode.end() || nit->second == nullptr) return 0;
    TreeNode *nnode = nit->second;
    if (k <= 0) return nnode->id; //0th ancestor

    TreeNode *pnode = nnode->parent;
    while (pnode && (k > 1)) {
        pnode = pnode->parent;
        k--;
    }

    if (pnode) return pnode->id;
    return 0;
}

void AncestorTree::processQuery() {
    int qnum; std::cin >> qnum;
    int n1, n2;
    switch (qnum) {
      case 0: {
          std::cin >> n1 >> n2;
          addNode(n2, n1);
          break;
      }
      case 1: {
          std::cin >> n1;
          removeNode(n1);
          break;
      }
      case 2: {
          std::cin >> n1 >> n2;
          int ans = kthAncestor(n1, n2);
          std::cout << ans << std::endl;
          break;
      }
      default : 
          std::cout << "Unknown query type -> " << qnum << std::endl;
    }
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        AncestorTree kat;
        int queries; std::cin >> queries;
        for (int q=0; q<queries; q++) {
            kat.processQuery();
        }
    }
}

