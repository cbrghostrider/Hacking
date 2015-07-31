// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>

using std::unordered_set;
using std::vector;

struct Node {
    Node(int value) : val(value), children() {}
    int val;
    vector<Node*> children;
};

class SimilarPair {
public:
    SimilarPair(int n, int k);
    long long computeSimilarPairs();
    ~SimilarPair();
private:
    void dfs(Node* node, unordered_set<int>& ancestors);
    const int K;
    long long ctr;
    Node *root;
    vector<Node*> nodeList;
};

SimilarPair::SimilarPair(int n, int k)
: K(k), ctr(0), root(nullptr), nodeList() {
    //make nodes 0-indexed instead of 1-indexed
    for (int i=0; i<n; i++) {
        nodeList.push_back(new Node(i));
    }

    vector<int> hasParent(n, false);
    for (int i=0; i<n-1; i++) {
        int from, to; std::cin >> from >> to;
        from -= 1; to -= 1;
        nodeList[from]->children.push_back(nodeList[to]);
        hasParent[to] = true;
    }

    for (int i=0; i<hasParent.size(); i++) {
        if (hasParent[i] == false) {
            root = nodeList[i]; 
            break;
        }
    }
}

SimilarPair::~SimilarPair() {
    for (int i=0; i<nodeList.size(); i++) {
        delete nodeList[i];
    }
}

void SimilarPair::dfs(Node* node, unordered_set<int>& ancestors) {
    for (const int& anc : ancestors) {
        if (abs(anc - node->val) <= K) {
            ctr++;
        }
    }
    ancestors.insert(node->val);
    for (int i=0; i<node->children.size(); i++) {
        dfs(node->children[i], ancestors);
    }
    ancestors.erase(node->val);
}

long long SimilarPair::computeSimilarPairs() {
    unordered_set<int> ancestors;
    dfs(root, ancestors);
    return ctr;
}

int main() {
    int n, k; std::cin >> n >> k;
    SimilarPair sp(n, k);
    long long ans = sp.computeSimilarPairs();
    std::cout << ans << std::endl;
}


