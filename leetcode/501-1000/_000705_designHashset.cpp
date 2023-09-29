class MyHashSet {
    struct Node {
        Node* next = nullptr;
        int value = 0;
    };
    int PRIME = 97;
    
    // Potential optimization from O(n) -> O(log n) operations is to keep the collision list sorted.
    // and perform binary search during add/search/delete.
    vector<Node*> hash_table;
    
public:
    MyHashSet() {
        hash_table = vector<Node*>(PRIME, nullptr);
    }
    
    // add is O(k) -- potentially O(n) operation
    void add(int key) {
        if (contains(key)) return;
        
        int bucket = key % PRIME;
        Node* node = new Node{hash_table[bucket], key};
        hash_table[bucket] = node;
    }
    
    // remove is O(k) -- potentially O(n) operation
    void remove(int key) {
        int bucket = key % PRIME;
        
        Node *prev_node = hash_table[bucket];
        if (prev_node == nullptr) return;  // should not happen
        if (prev_node->value == key) {
            hash_table[bucket] = prev_node->next;
            delete prev_node;
            return;
        }
        
        Node *node = prev_node->next;
        while (node != nullptr) {
            if (node->value == key) {
                prev_node->next = node->next;
                delete node;
                return;
            }
            prev_node = node;
            node = node->next;
        }
    }
    
    // contains is O(k) -- potentially O(n) operation
    bool contains(int key) {
        int bucket = key % PRIME;
        Node *node = hash_table[bucket];
        while (node != nullptr) {
            if (node->value == key) {
                return true;
            }
            node = node->next;
        }
        return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
