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
    TreeNode* str2Tree(const string& s, int& ptr) {
        int pos = s.find_first_of("()", ptr);
        int len = pos == string::npos ? s.size() - ptr : pos - ptr;
        int val = std::stoi(s.substr(ptr, len));
        ptr = pos;
        TreeNode *me = new TreeNode(val);
        
        if (ptr == string::npos || s[ptr] == ')') {
            ptr++;
            return me;
        }
        
        TreeNode *left = nullptr, *right=nullptr;
        if (s[ptr] == '(') {
            ptr++;
            left = str2Tree(s, ptr);
        }
        if (s[ptr] == '(') {
            ptr++;
            right = str2Tree(s, ptr);
        }
        ptr++;  // consume ')'
        me->left = left;
        me->right = right;
        return me;
    }
public:
    TreeNode* str2tree(string s) {
        if (s == "") return nullptr;
        int ptr=0;
        return str2Tree(s, ptr);
    }
};
