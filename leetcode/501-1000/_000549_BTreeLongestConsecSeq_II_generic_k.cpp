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
    struct APInfo {          // Records arithmetic progression info between node and a child.
        bool in_ap = false;  // if I have a child, I am in an AP with that child
        int ap_val = 0;      // AP value between node and child
        int ap_len = 0;      // len of AP continued with this child (may involve subtree)
    };
    struct Info {
        APInfo l;        // AP info for my left
        APInfo r;        // AP info for my right
        int max_left=0;  // in left-subtree, what's the max path len (may be l.ap_len)
        int max_right=0; // in right-subtree, what's the max path len (may be r.ap_len)
        int max_cross=0; // may involve cross-child AP
    };
    
    // 
    // Initially I wrote a solution assuming I have to find an AP of any value k.
    // Later I found out that the problem is SPECIFICALLY looking only for an AP of 1.
    //
    // So I added "FIXED" blocks, that restrict the problem thus.
    // They are marked with the comment "FIXED" in code.
    //
    // Removing that code should give the longest path len for any generic value k 
    // (k is found implicitly during the search)
    //
    Info traverse(TreeNode* root) {
        if (root == nullptr) return Info();
        
        Info lhs = traverse(root->left);
        Info rhs = traverse(root->right);
        
        Info my_info;
        my_info.max_cross = 1;  // if I am a at least a leaf node, or I don't have a cross AP.
        
        if (root->left) {
            my_info.l.in_ap = true;
            my_info.l.ap_val = root->val - root->left->val;
            my_info.l.ap_len = 2;
            if (lhs.l.in_ap && lhs.l.ap_val == my_info.l.ap_val) {
                my_info.l.ap_len = std::max(1 + lhs.l.ap_len, my_info.l.ap_len);
            }
            if (lhs.r.in_ap && lhs.r.ap_val == my_info.l.ap_val) {
                my_info.l.ap_len = std::max(1 + lhs.r.ap_len, my_info.l.ap_len);
            }
            if (my_info.l.ap_val != 1 && my_info.l.ap_val != -1) {  // FIXED for AP = 1
                my_info.l.ap_len = 1;
                my_info.l.in_ap = false;
                my_info.l.ap_val=0;
            }

        }
        if (root->right) {
            my_info.r.in_ap = true;
            my_info.r.ap_val = root->val - root->right->val;
            my_info.r.ap_len = 2;
            if (rhs.l.in_ap && rhs.l.ap_val == my_info.r.ap_val) {
                my_info.r.ap_len = std::max(1 + rhs.l.ap_len, my_info.r.ap_len);
            }
            if (rhs.r.in_ap && rhs.r.ap_val == my_info.r.ap_val) {
                my_info.r.ap_len = std::max(1 + rhs.r.ap_len, my_info.r.ap_len);
            }
            if (my_info.r.ap_val != 1 && my_info.r.ap_val != -1) {  // FIXED for AP = 1
                my_info.r.ap_len = 1;
                my_info.r.in_ap = false;
                my_info.r.ap_val=0;
            }            
        }        
        if (root->left && root->right) {
            if (my_info.l.ap_val == -1* my_info.r.ap_val) {
                my_info.max_cross = my_info.l.ap_len + my_info.r.ap_len - 1;
            }
            if (my_info.r.ap_val != 1 && my_info.r.ap_val != -1) {  // FIXED for AP = 1
                my_info.max_cross = 1;
            }  
        }
        my_info.max_left = std::max(std::max(lhs.max_left, my_info.l.ap_len), 
                                    std::max(lhs.max_right, lhs.max_cross));
        my_info.max_right = std::max(std::max(rhs.max_left, my_info.r.ap_len), 
                                     std::max(rhs.max_right, rhs.max_cross));
        return my_info;
    }
public:
    int longestConsecutive(TreeNode* root) {
        if (root == nullptr) return 0;
        Info info = traverse(root);
        return std::max(info.max_cross, std::max(info.max_left, info.max_right));
    }
};
