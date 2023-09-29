class MapSum {
    struct Node {
        bool has_val = false;
        int val=0;
        vector<Node*> children;
        
        Node() {children = vector<Node*>(26, nullptr);}
        Node* getChild(char ch) {            
            return children[ch - 'a'];
        }
        void createChild(char ch) {
            if (children[ch-'a'] != nullptr) return;
            children[ch-'a'] = new Node();
        }        
    };
    
    Node* trie=nullptr;
        
    void insertInTrie(const string& key, int val) {
        Node* node = trie;
        for (char ch : key) {
            Node* next = node->getChild(ch);
            if (next == nullptr) {
                node->createChild(ch);
                next = node->getChild(ch);
            }
            node = next;
        }
        node->val = val;
        node->has_val = true;
    }
    
    // recursively computes key vals
    int traverse(Node* node) {
        if (node == nullptr) return 0;
        
        int total = node->has_val ? node->val : 0;
        for (Node* child : node->children) {
            total += traverse(child);
        }
        return total;
    }
    
public:
    MapSum() {
        trie = new Node();
    }
    
    // O(k) time; k = |key|
    void insert(string key, int val) {
        insertInTrie(key, val);
    }
    
    // O(p + nk) time; p = |prefix|, n = num keys, k = |key|
    int sum(string prefix) {
        Node* node = trie;
        for (char ch : prefix) {
            node = node->getChild(ch);
            if (node == nullptr) return 0;  // nothing has this prefix
        }
        int total = traverse(node);
        return total;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
