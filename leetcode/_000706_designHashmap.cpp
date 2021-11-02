class MyHashMap {
    struct Node {
        Node* next = nullptr;
        int key = 0;
        int value = 0;
    };
    int PRIME = 97;
    
    // Potential optimization from O(n) -> O(log n) operations is to keep the collision list sorted.
    // and perform binary search during add/search/delete.
    vector<Node*> hash_table;
    
public:
    MyHashMap() {
        hash_table = vector<Node*>(PRIME, nullptr);
    }
    
    // put is O(k) -- potentially O(n) operation
    void put(int key, int value) {
        int bucket = key % PRIME;
        Node *node = hash_table[bucket];
        
        if (node == nullptr) { // empty bucket
            hash_table[bucket] = new Node{nullptr, key, value};
            return;
        }
        
        if (node->key == key) {
            node->value = value;
            return;
        }
        
        while (node->next) {
            node = node->next;
            if (node->key == key) {
                node->value = value;
                return;
            }
        }
        
        // Not found, insert at the end
        Node *last = new Node{nullptr, key, value};
        node->next = last;
    }
    
    // get is O(k) -- potentially O(n) operation
    int get(int key) {
        int bucket = key % PRIME;
        Node *node = hash_table[bucket];
        while (node) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        return -1;
    }
       
    // remove is O(k) -- potentially O(n) operation
    void remove(int key) {
        int bucket = key % PRIME;
        
        Node *prev_node = hash_table[bucket];
        if (prev_node == nullptr) return;  // should not happen
        if (prev_node->key == key) {
            hash_table[bucket] = prev_node->next;
            delete prev_node;
            return;
        }
        
        Node *node = prev_node->next;
        while (node != nullptr) {
            if (node->key == key) {
                prev_node->next = node->next;
                delete node;
                return;
            }
            prev_node = node;
            node = node->next;
        }
    }
    
public:

};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
