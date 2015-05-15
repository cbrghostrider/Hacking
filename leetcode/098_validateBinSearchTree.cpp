/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    //for a BST rooted somewhere: (is-binary-search-tree?, lowest elem, highest elem)
    typedef tuple<bool, int, int> BSTResult;

    BSTResult validBST(TreeNode* root) {
        if (root == NULL) return make_tuple(true, 0, 0);
        BSTResult lhs = validBST(root->left);
        BSTResult rhs = validBST(root->right);
        bool highCmp = root->left ?  (root->val > std::get<2>(lhs)) : true;
        bool lowCmp  = root->right ? (root->val < std::get<1>(rhs)) : true;
        int myHighest = root->right ? std::get<2>(rhs) : root->val;
        int myLowest  = root->left ?  std::get<1>(lhs) : root->val;
        return (make_tuple(highCmp && lowCmp && std::get<0>(lhs) && std::get<0>(rhs), myLowest, myHighest));
    }
public:
    bool isValidBST(TreeNode* root) {
        return std::get<0>(validBST(root));
    }
};
