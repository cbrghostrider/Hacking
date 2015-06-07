// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// Very cool problem! Here is my solution:
// MaxPaths stores 2 candidates:
//      1. (path that goes through me, possibly down to lhs or rhs , AND
//      2. path that goes from my lhs, through me, cross to rhs)
//         note that first result only eats up one node, 
//         while second result is complete (eats both src and dst nodes)
//         [By complete, I mean that we can't add on nodes to this path in recursion]
//
// To find maxSumPath of the entire tree, we do this recursively
// For (1) [remember this choice only consumes 1 node]
//     a. choose a path that goes through me concat w/ best lhs path OR
//     b. choose a path that goes thorugh me concat w/ best rhs path OR
//     c. Or just myself only (if lhs and rhs are all -ve for example!)
//
// For (2), we have the following candidates:
//      my cross path could be either
//       a. from me to my lhs' best end
//       b. from me to my rhs' best end
//       c. from myself to myself
//       d. from somewhere in my lhs, through me, to somewhere in my rhs (myCrossPath)
//       e. my lhs' crosspath
//       f. my rhs' crosspath
//     Note that a, b, c above are same as first case! So I can re-use that computation!
class Solution {
    typedef pair<int, int> MaxPaths; 
    
    MaxPaths maxPathSumPrime(TreeNode* root) {
        if (root == NULL) return (make_pair(0, std::numeric_limits<int>::min()));
        MaxPaths lhsResults = maxPathSumPrime(root->left);
        MaxPaths rhsResults = maxPathSumPrime(root->right);
        int justMe    = root->val;
        int myCrossPath = lhsResults.first + rhsResults.first + justMe;
        int myfirst = std::max(justMe, std::max(lhsResults.first + justMe, rhsResults.first + justMe));
        int mysecond = std::max(myfirst, std::max(myCrossPath, std::max(lhsResults.second, rhsResults.second)));
        return (make_pair(myfirst, mysecond));
    }
public:
    int maxPathSum(TreeNode* root) {
        MaxPaths result = maxPathSumPrime(root);
        return (std::max(result.first, result.second));
    }
};
