class Solution {
    // For a binary tree to be valid:
    // 
    // 1. EXACTLY 1 node has no parent.
    // 2. All other nodes have EXACTLY 1 parent.
    // 3. No node has more than 2 children. (Implicit in input format)
    // 4. If both left and right children exist, they must be different. Covered by 2.
    // 5. No cycle.
    // 6. Two different parents can't have the same child. Covered by 2.
    //
    // Easiest thing to do is:
    // 1. Find root (thing with no parent); if 0 or more than 1, then fail.
    // 2. Traverse root.
    //    a. Make sure everything is visited.
    //    b. Make sure nothing got visited twice.

    unordered_set<int> has_parent;
    unordered_set<int> visited;
public:
    
    // returns true if there's a cycle
    bool visit(vector<int>& leftChild, vector<int>& rightChild, int i) {
        int lchild = leftChild[i];
        int rchild = rightChild[i];
        
        if (lchild != -1) {
            if (visited.find(lchild) != visited.end()) return true;
            visited.insert(lchild);
            bool v = visit(leftChild, rightChild, lchild);
            if (v) return true;
        }
        if (rchild != -1) {
            if (visited.find(rchild) != visited.end()) return true;
            visited.insert(rchild);
            bool v = visit(leftChild, rightChild, rchild);
            if (v) return true;
        }
        return false;
    }
    
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        
        for (int i=0; i<n; i++) {
            int lchild = leftChild[i];
            int rchild = rightChild[i];
            if (lchild != -1) {has_parent.insert(lchild);}
            if (rchild != -1) {has_parent.insert(rchild);}
        }
        
        if (has_parent.size() != n-1) return false;
        int root = -1;
        for (int i=0; i<n; i++) {
            if (has_parent.find(i) == has_parent.end()) {
                root = i;
                break;
            }
        }
        
        visited.insert(root);
        if (visit(leftChild, rightChild, root)) return false;
        
        // check that everything is visited
        for (int i=0; i<n; i++) {
            if (visited.find(i) == visited.end()) return false;
        }
        return true;
    }
};
