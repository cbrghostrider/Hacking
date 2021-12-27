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
    // key = level
    // value = leftmost or rightmost node number discovered at level
    unordered_map<int, long> leftvals, rightvals;
    
    // my_level the level of node in the tree
    // my_num is the node number for node (parent p; children 2p+1, 2p+2)
    void traverse(TreeNode* node, int my_level, long my_num) {
        if (node == nullptr) return;
        
        if (leftvals.find(my_level) == leftvals.end()) {
            leftvals[my_level] = my_num;
            rightvals[my_level] = my_num;
        } else {
            leftvals[my_level] = std::min(my_num, leftvals[my_level]);
            rightvals[my_level] = std::max(my_num, rightvals[my_level]);
        }
        if (node->left) traverse(node->left, my_level+1, 2*my_num+1);
        if (node->right) traverse(node->right, my_level+1, 2*my_num+2);
    }
public:
    // Solution is functionally correct, but gets runtime error for large inputs.
    //
    // The input has up to 3000 nodes. If the tree is a simple linked list
    // e.g. having only left children, it will have 3000 levels.
    // My child "labeling" scheme puts 2^level node nums at each level
    // so the my_num parameter will overflow quickly in traverse.
    int widthOfBinaryTree(TreeNode* root) {
        traverse(root, 0, 0);
        int max_width = 0;
        for (int i=0; i<leftvals.size(); i++) {
            int my_width = rightvals[i]-leftvals[i]+1;
            max_width = std::max(my_width, max_width);
        }
        return max_width;
    }
};
