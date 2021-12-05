/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     Node *left;
 *     Node *right;
 *     Node *random;
 *     Node() : val(0), left(nullptr), right(nullptr), random(nullptr) {}
 *     Node(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
 *     Node(int x, Node *left, Node *right, Node *random) : val(x), left(left), right(right), random(random) {}
 * };
 */

class Solution {
    unordered_map<Node*, NodeCopy*> copy_map;
public:
    // Recursive.
    // O(n) time, O(n) space for ans.
    NodeCopy* copyRandomBinaryTree_R(Node* root) {
        if (root == nullptr) return nullptr;
        if (copy_map.find(root) != copy_map.end()) return copy_map[root];
        
        NodeCopy *me = new NodeCopy(root->val);
        copy_map[root] = me;
        
        me->left = copyRandomBinaryTree_R(root->left);
        me->right = copyRandomBinaryTree_R(root->right);
        me->random = copyRandomBinaryTree_R(root->random);
        return me;
    }
    
    // Iterative.
    NodeCopy* copyRandomBinaryTree(Node* root) {
        if (root == nullptr) return nullptr;
        vector<Node*> stack;
        
        stack.push_back(root);
        unordered_map<Node*, bool> visited;
        visited[root] = true;
        while (!stack.empty()) {
            if (stack.back()->left && !visited[stack.back()->left]) {
                visited[stack.back()->left] = true;
                stack.push_back(stack.back()->left);
                continue;
            }
            if (stack.back()->right && !visited[stack.back()->right]) {
                visited[stack.back()->right] = true;
                stack.push_back(stack.back()->right);
                continue;
            }
            
            
            Node *me = stack.back(); 
            stack.pop_back();
            NodeCopy *me_copy = new NodeCopy(me->val);
            copy_map[me] = me_copy;
            me_copy->left = (me->left == nullptr ? nullptr : copy_map[me->left]);
            me_copy->right = (me->right == nullptr ? nullptr : copy_map[me->right]);
            me_copy->random = (NodeCopy*)(me->random);  // will be fixed up later
        }
        
        vector<NodeCopy*> copy_stack;
        unordered_map<NodeCopy*, bool> visited_copy;
        copy_stack.push_back(copy_map[root]);
        visited_copy[copy_map[root]] = true;
        while (!copy_stack.empty()) {
            if (copy_stack.back()->left && !visited_copy[copy_stack.back()->left]) {
                visited_copy[copy_stack.back()->left] = true;
                copy_stack.push_back(copy_stack.back()->left);
                continue;
            }
            if (copy_stack.back()->right && !visited_copy[copy_stack.back()->right]) {
                visited_copy[copy_stack.back()->right] = true;
                copy_stack.push_back(copy_stack.back()->right);
                continue;
            }
            copy_stack.back()->random = copy_map[(Node*)(copy_stack.back()->random)];
            copy_stack.pop_back();
        }
        
        return copy_map[root];
    }
};
