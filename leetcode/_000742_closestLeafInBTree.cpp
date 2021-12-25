/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
constexpr int MAX=10000;
class Solution {
    // For the found node, the closest leaf is either:
    // 1. In one of its child trees.
    // 2. In one of the other children trees of one of its ancestors
    //
    // For #1, we need the length of the path from "found node" to its least depth leaf.
    // For #2, we need the lengths of
    //      2.a. Path from least depth leaf to common ancestor
    //      2.b. Path from found node to common ancestor
    struct Info {
        bool found=false;         // was leaf node found in this subtree
        int found_at_level=MAX;   // the level (relative to subtree root) where it was found
        int child_leaf=MAX;       // the value of the closest child leaf for found node        
        int best=MAX;             // the best candidate at this subtree (-1 if not found in subtree)
        int value=MAX;            // the value for the leaf node chosen
    };
   
    // 
    // Hmm, I'm not happy with this solution.
    // Looks way too complicated.
    //
    Info traverse(TreeNode* node, int k) {
        if (node == nullptr) return Info();
        if (node->val != k && node->left == nullptr && node->right == nullptr) {
            return {false, MAX, 0, MAX, node->val};
        }
        if (node->val == k && node->left == nullptr && node->right == nullptr) {
            return {true, 0, 0, 0, node->val};
        }
        
        Info ret;
        Info lhs = traverse(node->left, k);
        Info rhs = traverse(node->right, k);
        
        if (node->val == k) {
            ret.found = true;
            ret.found_at_level = 0;
            ret.child_leaf = 1 + std::min(lhs.child_leaf, rhs.child_leaf);
            ret.best = ret.child_leaf;
            if (lhs.child_leaf <= rhs.child_leaf) ret.value = lhs.value;
            else ret.value = rhs.value;
            return ret;
        }
        
        if (lhs.found == false && rhs.found == false) {
            ret.child_leaf = 1 + std::min(lhs.child_leaf, rhs.child_leaf);
            if (lhs.child_leaf <= rhs.child_leaf) ret.value = lhs.value;
            else ret.value = rhs.value;            
            return ret;
        }
        
        ret.found = true;
        
        if (lhs.found == false) {
            ret.found_at_level = rhs.found_at_level+1;
            ret.child_leaf = 1 + std::min(lhs.child_leaf, rhs.child_leaf);
            int cross = rhs.found_at_level + lhs.child_leaf + 1 + 1;
            ret.best = std::min(rhs.best, cross);
            ret.value = (ret.best == cross ? lhs.value : rhs.value);
            return ret;
        }
        
        // found on the lhs
        ret.found_at_level = lhs.found_at_level+1;
        ret.child_leaf = 1 + std::min(rhs.child_leaf, lhs.child_leaf);
        int cross = lhs.found_at_level + rhs.child_leaf + 1 + 1;
        ret.best = std::min(lhs.best, cross);        
        ret.value = (ret.best == lhs.best ? lhs.value : rhs.value);
        return ret;
    }
public:
    int findClosestLeaf(TreeNode* root, int k) {
        Info info = traverse(root, k);
        return (info.best >= MAX ? root->val : info.value);
    }
};
