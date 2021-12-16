/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "N:";
        string my_val = std::to_string(root->val);
        return my_val + ":" + serialize(root->left) + serialize(root->right); 
    }
    
    TreeNode* deserialize_(const string& data, int& ptr) {
        if (data[ptr] == 'N') {
            ptr += 2;
            return nullptr;
        }
        
        int pos = data.find_first_of(":", ptr);
        int len = pos == string::npos ? data.size()-ptr : pos - ptr;
        int my_val = std::stoi(data.substr(ptr, len));
        
        ptr += len + 1;
        
        TreeNode* left = deserialize_(data, ptr);
        TreeNode* right = deserialize_(data, ptr);
        return new TreeNode(my_val, left, right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int ptr=0;
        return deserialize_(data, ptr);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
