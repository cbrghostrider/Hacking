// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using std::string;

/**
 * Definition for a binary tree node.*/
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 
class Codec {
public:
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == NULL) {
            return "##";
        }
        string retval("#");
        
        retval += std::to_string(root->val);
        retval += serialize(root->left);
        retval += serialize(root->right);
        
        retval += "#";
        return retval;
    }
    
    TreeNode* deserialize_(string& data, int& pos) {
        if (data[pos] == '#' && data[pos+1] == '#') {
            pos += 2;
            return NULL;
        }
        
        pos++; //match open '#'
        
        size_t limiter = data.find_first_of('#', pos);
        string value = data.substr(pos, limiter-pos+1);
        int val = std::stoi(value);
        TreeNode* retval = new TreeNode(val);
        
        //pos += (limiter-pos+1);
        pos = limiter;
        
        TreeNode* left = deserialize_(data, pos);
        TreeNode* right = deserialize_(data, pos);
        retval->left = left;
        retval->right = right;
        
        pos++; //match close '#'
        return retval;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int pos=0;
        return deserialize_(data, pos);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main() {
    Codec codec;

    TreeNode* root = new TreeNode(1);
    TreeNode* left = new TreeNode(2);
    root->left = left;

    string str = codec.serialize(root);
    std::cout << str << std::endl;

    TreeNode* ret = codec.deserialize(codec.serialize(root));
}
