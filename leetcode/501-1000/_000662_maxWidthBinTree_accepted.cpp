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
    // We can define the "coordinate" of a node within the tree as
    // a vector of path decisions: -1 to go left, +1 to go right.
    // e.g. first node at 3rd level is : {-1, -1, -1} etc.
    //
    // Any time we "visit" a level, the node stores its coordinate in least, greatest
    // if it is the least or greatest coordinate at that level
    // (coordinate comparison is done in lockstep from the beginning)
    //
    // At the end, we STRIP OUT THE LEADING COMMON NUMBERS between least greatest at each level
    // and then compute the "width" by converting the coordinate to a number
    // Note that this number is the same scheme as before (parent p: children 2p+1, 2p+2)
    // But since we stripped out the common portions, now these will fit within our integer
    
    bool lessThan(const vector<int>& a, const vector<int>& b) {
        // if (a.size() != b.size()) {return false;}  // panic! should not happen
        for (int i=0; i<a.size(); i++) {
            if (a[i] < b[i]) return true;
            if (a[i] > b[i]) return false;
        }
        return false;
    }
    
    bool greaterThan(const vector<int>& a, const vector<int>& b) {
        // if (a.size() != b.size()) {return false;}  // panic! should not happen
        for (int i=0; i<a.size(); i++) {
            if (a[i] > b[i]) return true;
            if (a[i] < b[i]) return false;
        }
        return false;
    }
    
    // from is the first index that mismatched
    unsigned long convertToNum(const vector<int>& a, int from) {
        unsigned long p=0;
        for (int i=from; i<a.size(); i++) {
            if (a[i] == -1) {p = 2*p+1;}
            else {p = 2*p+2;}
        }
        return p;
    }
    
    int width(const vector<int>& a, const vector<int>& b) {
        // if (a.size() != b.size()) {return false;}  // panic! should not happen
        if (a == b) return 1;
        
        int index=0;
        for (int i=0; i<a.size(); i++) {
            if (a[i] != b[i]) {
                index = i;
                break;
            }
        }
        
        unsigned long n1 = convertToNum(a, index);
        unsigned long n2 = convertToNum(b, index);
        return (n2-n1+1);
    }
    
    unordered_map<int, vector<int>> smallest, largest;
    
    void traverse(TreeNode* node, int my_level, vector<int>& path) {
        if (node == nullptr) return;
        
        if (smallest.find(my_level) == smallest.end()) {
            smallest[my_level] = path;
            largest[my_level] = path;            
        } else {
            if (lessThan(path, smallest[my_level])) {
                smallest[my_level] = path;
            }
            if (greaterThan(path, largest[my_level])) {
                largest[my_level] = path;
            }
        }
        
        path.push_back(-1);
        traverse(node->left, my_level+1, path);
        path.pop_back();
        
        path.push_back(1);
        traverse(node->right, my_level+1, path);
        path.pop_back();
    }
    
public:
    int widthOfBinaryTree(TreeNode* root) {        
        vector<int> path;
        traverse(root, 0, path);
        
        auto &s=smallest, &l=largest;
        
        int max_width = 0;
        for (int i=0; i<smallest.size(); i++) {
            int my_width = width(smallest[i], largest[i]);
            max_width = std::max(my_width, max_width);
        }
        return max_width;
    }
};
