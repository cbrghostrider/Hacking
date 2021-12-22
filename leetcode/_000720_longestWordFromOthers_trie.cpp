class Solution {
    struct Node {
        char ch = ' ';
        bool ends_here = false;
        vector<Node*> children;
     
        Node(char c = ' ', bool ends = false) : ch(c), ends_here(ends) { 
            children = vector<Node*>(26, nullptr); 
        }
        ~Node() { for (Node* n : children) {delete n;} }
        
        // used to walk the tree, also mark nodes as word endings if needed
        Node* walk(char ch, bool done=false) {
            if (children[ch-'a'] != nullptr) {
                if (done == true) { children[ch-'a']->ends_here = true; }
                return children[ch-'a'];
            }
            children[ch-'a'] = new Node({ch, done});
            return children[ch-'a'];
        }
        bool ends() const {return ends_here;}
        void markEnd() {ends_here = true;}
    };
    
    Node* root;
    
    // returns the value of the maxlen path
    string dfs(Node* node) {
        if (node == nullptr || node->ends_here == false) {return "";}
        string child_best;
        for (Node* n : node->children) {
            string c = dfs(n);
            if (c.size() > child_best.size()) {child_best = c;}
        }
        return std::string(1, node->ch) + child_best;
    }
public:
    // O(mn) to build, and O(mn) to walk the tree.
    string longestWord(vector<string>& words) {
        root = new Node();
        
        // Build the retrieval tree.
        for (const string& word : words) {
            Node* node = root;
            for (int i=0; i<word.size(); i++) {
                node = node->walk(word[i], i==word.size()-1);
            }
        }
        
        // Walk the retrieval tree.
        string best;
        for (Node* n : root->children) {
            string c = dfs(n);
            if (c.size() > best.size()) {best = c;}
        }
        return best;
    }
};
