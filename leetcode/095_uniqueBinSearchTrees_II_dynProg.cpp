//Attempt 1: solution works fine in linux, tested it
//but too slow, online judge (OJ) gives time limit exceeded
//need to find a way to speed it up
//problem is that I am generating too many combinations, and throwing out most of them
//I need a way to generate fewer combinations to begin with, rather than filtering out the bad ones
//The algorithmic complexity lower bound on this problem is omega(C(n)) where C(n) is the catalan number of n

//
//EDIT: Check attempt 2 (better). That is much cleaner code, and solves this problem (OJ accepted).
//
#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <limits>

using std::unordered_set;
using std::vector;
using std::pair;
using std::make_pair;

/**
 * Definition for a binary tree node.*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        
        //Index i: Contains all trees containing "i" nodes
        //         each tree is accompanied by a set of numbers used in that tree
        vector<pair<TreeNode*, unordered_set<int>>> cache[n+1];
        unordered_set<int> nothing;
        vector<pair<TreeNode*, unordered_set<int>>> nothVect(1, make_pair((TreeNode*)NULL, nothing));
        cache[0] = nothVect;
        
        for (int nodes=1; nodes<=n; nodes++) {  //go through all number of nodes
            vector<pair<TreeNode*, unordered_set<int>>> record;
            for (int root=1; root<=n; root++) { //go through all choices of root
                for (int numLhs=0; numLhs<=nodes-1; numLhs++) { //number of nodes in LHS subtree
                    int numRhs = nodes - numLhs - 1;            //number of nodes in RHS subtree
                    auto lhsCache = cache[numLhs];
                    auto rhsCache = cache[numRhs];
                    for (auto lhsinfo : lhsCache) {
                        for (auto rhsinfo : rhsCache) {
                            unordered_set<int> interSet, unionSet;
                            set_intersection(lhsinfo.second.begin(), lhsinfo.second.end(), 
                                             rhsinfo.second.begin(), rhsinfo.second.end(), 
                                             std::inserter(interSet, interSet.begin()));
                            if (!interSet.empty()) continue;                     //conflicting sets
                            
                            set_union(lhsinfo.second.begin(), lhsinfo.second.end(), 
                                      rhsinfo.second.begin(), rhsinfo.second.end(), 
                                      std::inserter(unionSet, unionSet.begin()));
                            if (unionSet.find(root) != unionSet.end()) continue; //root was re-used
                            
                            int maxlhs = std::accumulate(lhsinfo.second.begin(), lhsinfo.second.end(), 
                                                         std::numeric_limits<int>::min(), 
                                                         [] (const int& acc, const int& num) -> int {
                                                             return (acc > num ? acc : num);
                                                         });
                            int minrhs = std::accumulate(rhsinfo.second.begin(), rhsinfo.second.end(), 
                                                         std::numeric_limits<int>::max(), 
                                                         [] (const int& acc, const int& num) -> int {
                                                             return (acc < num ? acc : num);
                                                         });
                            if (maxlhs > root || minrhs < root) continue;        //not a binary search tree
                            
                            unionSet.insert(root);                               //for my solution
                            TreeNode* rootnd = new TreeNode(root);
                            rootnd->left  = lhsinfo.first;
                            rootnd->right = rhsinfo.first;
                            record.push_back(make_pair(rootnd, unionSet));
                        }
                    }
                }
            }
            cache[nodes] = record;
            record.clear();
        }
        vector<TreeNode*> retval;
        for (auto cand : cache[n]) {
            retval.push_back(cand.first);
        }
        return retval;
    }
};


static void showTree(TreeNode* nd) 
{  
    if (nd == NULL) {
        std::cout << "null ";
        return;
    }
    std::cout << nd->val << " ";
    showTree(nd->left);
    showTree(nd->right);
}

int main() 
{
    Solution sln;
    vector<TreeNode*> ans = sln.generateTrees(7);
    for (TreeNode*& nd : ans) {
        showTree(nd);
        std::cout << std::endl;
    }
}



