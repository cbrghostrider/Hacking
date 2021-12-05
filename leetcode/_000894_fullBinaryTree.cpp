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
    TreeNode* clone(TreeNode* root) {
        if (root == nullptr) return nullptr;
        TreeNode* left = clone(root->left);
        TreeNode* right = clone(root->right);
        TreeNode* me = new TreeNode();
        me->left = left;
        me->right = right;
        return me;
    }
    
    // recurses to find all the leaves, 
    // inserts 2 new nodes at position i if it exists, else,
    // decrements pos if it consumes places where it didn't insert anything.
    void insertAt(TreeNode* node, int& pos) {
        if (node == nullptr || pos < 1) return;
        
        if (node->left == nullptr && node->right == nullptr) {
            if (pos == 1) {
                node->left = new TreeNode();
                node->right = new TreeNode();
                pos -= 2;
                return;
            } else {
                pos -= 2;
            }
        }

        insertAt(node->left, pos);
        if (pos < 0) return;
        insertAt(node->right, pos);
    }
    
    string signature(TreeNode* tree) {
        if (tree == nullptr) return "N";
        return ("0" + signature(tree->left) + signature(tree->right));
    }
public:

    vector<TreeNode*> allPossibleFBT2(int n) {
        if (n % 2 == 0) return {};
        if (n == 1) return {new TreeNode()};
        
        vector<TreeNode*> ans;
        unordered_set<string> signatures;
        vector<TreeNode*> nm2 = allPossibleFBT(n-2);
        for (TreeNode* node : nm2) {
            for (int i=0; i<n-1; i+=2) {
                int pos = i+1;
                TreeNode* tree = clone(node);
                insertAt(tree, pos);
                string sig = signature(tree);
                if (signatures.find(sig) == signatures.end()) {
                    ans.push_back(tree);
                    signatures.insert(sig);
                }
            }
        }      
        return ans;
    }
    
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Iterative DP solution.
    ///////////////////////////////////////////////////////////////////////////////////////////
    vector<TreeNode*> allPossibleFBT(int n) {
        if (n % 2 == 0) return {};
        if (n == 1) return {new TreeNode()};
        
        unordered_map<int, vector<TreeNode*>> ans;
        ans[1] = vector<TreeNode*>(1, new TreeNode());
        for (int ni=3; ni<=n; ni+=2) {
            // Create a new root node, consumes 1 count.
            // Divide up the remaining (ni-1) count into 2 nums (l, r)
            // l, r are both odd, and l+r=ni-1
            for (int l=1, r=ni-1-1; l<=ni-1-1; l+=2, r-=2) {
                vector<TreeNode*>& ltrees = ans[l];
                vector<TreeNode*>& rtrees = ans[r];
                for (TreeNode* ltree : ltrees) {
                    for (TreeNode* rtree: rtrees) {
                        TreeNode* root = new TreeNode();
                        root->left = ltree;
                        root->right = rtree;
                        ans[ni].push_back(root);
                    }
                }
            }
        }
        return ans[n];
    }
};


