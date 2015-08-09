// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(ht) space, and O(ht) time
//
class Solution {
    enum Direction {LEFT, RIGHT};
    bool findNode(TreeNode* root, TreeNode* n, vector<Direction>& path) {
        if (root == nullptr || n == nullptr) return false;
        if (root == n) return true;
        
        //try left side
        path.push_back(LEFT);
        bool findval = findNode(root->left, n, path);
        if (findval) return true;
        
        //try right side
        path.pop_back();
        path.push_back(RIGHT);
        findval = findNode(root->right, n, path);
        if (findval) return true;
        
        path.pop_back();
        return false;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<Direction> pdirs, qdirs;
        bool fp = findNode(root, p, pdirs);
        bool fq = findNode(root, q, qdirs);
        
        if (fp == false || fq == false) return 0;
        
        int ind=0;
        while (root && ind < pdirs.size() && ind < qdirs.size() && pdirs[ind] == qdirs[ind]) {
            if (pdirs[ind] == LEFT) {
                root = root->left;
            } else {
                root = root->right;
            }
            ind++;
        }
        return root;
    }
};
