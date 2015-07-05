// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Input format for this problem is messed up on hacker rank
// maybe a graph, and not a tree as stated in problem statement
// currently passing the first 6 tests, but timing out on rest
// need to debug... including code here only for completeness
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
using namespace std;

struct TreeNode {
    int val;
    int sum;
    bool visited;
    vector<TreeNode*> children;
    TreeNode(int value) : val(value), sum(0), visited(false), children() {} 
};

class Tree {
public:
    Tree();
    ~Tree();
    int getMinTreeDiff();
private:
    void readInput();
    int computeSum(TreeNode* node);
    void minTreeDiff(TreeNode* root, const int total);
    unsigned long long toKey(pair<int, int> nodes); 
    pair<int, int> fromKey(unsigned long long key);
    vector<TreeNode*> nodes;
    int minsofar;
};

Tree::Tree() 
: nodes(), minsofar() {
    readInput();
}

Tree::~Tree() {
    for (TreeNode*& node : nodes) {
        delete node;
    }
    nodes.clear();
}

unsigned long long Tree::toKey(pair<int, int> nodes) {
    return ((((unsigned long long)(nodes.first)) << 32) | ((unsigned long long)(nodes.second)));
}
pair<int, int> Tree::fromKey(unsigned long long key) {
    return make_pair((key >> 32) & 0xFFFFFFFF, (key) & 0xFFFFFFFF);
}

int Tree::computeSum(TreeNode* root) {
    if (root == nullptr) return 0;
    int childrensum = 0;
    for (TreeNode*& child : root->children) {
        childrensum += computeSum(child);
    }
    root->sum = childrensum + root->val;
    return root->sum;
}

int Tree::getMinTreeDiff() {
    minsofar = std::numeric_limits<int>::max();
    computeSum(nodes[0]);
    minTreeDiff(nodes[0], nodes[0]->sum); //assuming node 0 is root
    return minsofar;
}

void Tree::minTreeDiff(TreeNode *root, const int total) {
    if (root == nullptr) return;
    for (TreeNode*& child : root->children) {
        int childsum = child->sum;
        int withoutchildsum = total - childsum;
        int cand = abs(withoutchildsum - childsum);
        if (cand < minsofar) minsofar = cand;
        if ((withoutchildsum - childsum ) > minsofar) continue; //don't descend further
        minTreeDiff(child, total);
    }
}

void Tree::readInput() {
    int n; std::cin >> n;
    unordered_set<unsigned long long> edges;
    
    for (int i=0; i<n; i++) {
        int value; std::cin >> value;
        TreeNode* node = new TreeNode(value);
        nodes.push_back(node);
    }
    for (int i=0; i<n-1; i++) {
        int n1, n2; std::cin >> n1 >> n2;
        n1 -= 1; n2 -= 1; //make 0 indexed
        edges.insert(toKey(make_pair(n1, n2)));
    }
    
    int ctr = 0; //links made
    unordered_set<int> parents, children; 
    vector<bool> processed(n, false); //these guys have been processed
    children.insert(0);
    
    while (ctr < n-1) {
        parents = children; children.clear();
        for (const int& parent : parents) {
            unordered_set<unsigned long long> removeedges; //these ones are fully done
            
            for (auto edgekey : edges) {
                auto edge = fromKey(edgekey);
                if (edge.first != parent && edge.second != parent) continue;
                int child = (edge.first == parent) ? edge.second : edge.first;
                if (processed[child]) { //this was in fact, my parent's parent, not child
                    removeedges.insert(toKey(edge));
                    continue;
                }
                nodes[parent]->children.push_back(nodes[child]);
                children.insert(child);    
            }
            processed[parent] = true;
            for (auto redge : removeedges) {
                edges.erase(redge);
            }
        }
        ctr += children.size();
    }
 
}

int main() {
    Tree tree;
    int ans = tree.getMinTreeDiff();
    std::cout << ans << std::endl;
}

