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
class Solution {
    
    // elem_i is index of root, [left, right] are start and end indices of concat of left and right preorders
    // returns the index of the "boundary" i.e. index where right subtree begins
    int binarySearchBoundary(const vector<int>& preorder, int elem_i, int left, int right) {
        if (left == right) {
            if (preorder[right] > preorder[elem_i]) return right;
            return right+1;  // only left subtree existed, boundary beyond
        }
        int elem = preorder[elem_i];
        int mid = (left+right)/2;
        int midplus = mid+1;
        if (preorder[mid] < elem && preorder[midplus] > elem) return midplus;
        if (preorder[mid] < elem && preorder[midplus] < elem) {
            return binarySearchBoundary(preorder, elem_i, midplus, right);
        }
        return binarySearchBoundary(preorder, elem_i, left, mid);
    }
    
    // returns a BST for preorder[left, right] portion, inclusive.
    TreeNode* getBst(const vector<int>& preorder, int left, int right) {
        if (left == right) {
            return new TreeNode(preorder[left]);
        }
        if (left + 1 == right) {
            TreeNode *n1 = new TreeNode(preorder[left]);
            TreeNode *n2 = new TreeNode(preorder[right]);
            if (preorder[right] < preorder[left]) {
                n1->left = n2;
            } else {
                n1->right = n2;
            }
            return n1;
        }
        
        int boundary = binarySearchBoundary(preorder, left, left+1, right);
        TreeNode *me = new TreeNode(preorder[left]);
        TreeNode *ltree = (boundary == left+1  ? nullptr : getBst(preorder, left+1, boundary-1));
        TreeNode *rtree = (boundary == right+1 ? nullptr : getBst(preorder, boundary, right));
        me->left = ltree; me->right = rtree;
        return me;
    }
    
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return getBst(preorder, 0, preorder.size()-1);
    }
};
