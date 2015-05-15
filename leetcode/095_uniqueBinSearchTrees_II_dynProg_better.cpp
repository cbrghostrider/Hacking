//Attempt  2: Much better solution!
//Only generating needed candidates now, and it is lightning fast. 
//Accepted by online judge.
//
//Comparison: For     Input: [n=7,       n=8,       n=9, ............., n=15] 
//generating          Cases: [429,       1430,      4862, ............, 9694845]
//Runtime Attempt1 solution: [0.468 sec, 5.556 sec, 70.924 sec, ......, <did-not-attempt>]
//Runtime Attempt2 solution: [0 sec,     0 sec,     4 millisec, ......, 0.564 sec]

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
        if (n == 0) return vector<TreeNode*>(); 
        
        //dynamic programming cache[sz][at] records binary search trees
        //that are contiguous in sz nodes starting at at index
        //i.e. for BST tree size "sz" starting at "at" what are the candidates
        const int dim = n+1;
        vector<TreeNode*> cache[dim][dim];
        
        //base cases
        vector<TreeNode*> nullvect(1, (TreeNode*)NULL);
        for (int i=0; i<dim; i++) cache[0][i] = nullvect;
        for (int i=0; i<dim; i++) cache[i][0] = nullvect;

        for (int sz=1; sz<dim; sz++) {                               //this is the size of the tree
            vector<TreeNode*> record;
            for(int lhssize = 0; lhssize <= sz-1; lhssize++) {       //size of the LHS subtree
                int rhssize = sz - lhssize - 1;                      //size of the RHS subtree
                for (int at=1; (at<dim); at++) {                     //this is the chosen root
                    int lhsbegin = lhssize == 0 ? 0 : at - lhssize;  //index for LHS subtree
                    int rhsbegin = rhssize == 0 ? 0 : at+1;          //index for RHS subtree
                    if (lhsbegin &&  (lhsbegin + sz > dim)) continue;//can't go beyond end
                    if (!lhsbegin && (at + sz > dim)) continue;      //can't go beyond end
                    if (lhssize >= at) continue;                     //need enough nodes in LHS tree
                    vector<TreeNode*> lhstrees = cache[lhssize][lhsbegin];
                    vector<TreeNode*> rhstrees = cache[rhssize][rhsbegin];
                    for (TreeNode*& lhs : lhstrees) {
                        for (TreeNode*& rhs : rhstrees) {
                            TreeNode* me = new TreeNode(at);
                            me->left = lhs;
                            me->right = rhs;
                            
                            //this problem is caused by lhsbegin being 0, due to NULL LHS tree, 
                            //but we still have a valid candidate to record
                            cache[sz][lhsbegin ? lhsbegin : at].push_back(me);
                        }
                    }
                }
            }
        }

        return cache[n][1];
    }
};

void showTree(TreeNode* nd) 
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
    vector<TreeNode*> ans = sln.generateTrees(10);
    for (TreeNode*& nd : ans) {
        showTree(nd);
        std::cout << std::endl;
    }
}


