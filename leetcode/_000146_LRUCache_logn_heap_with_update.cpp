class LRUCache {
    unordered_map<int, int> key_to_index;
    unordered_map<int, int> key_to_val;
    
    int capacity=0;
    int time=0;    
    struct Elem {
        int key=0;
        int timestamp=0;
    };
    vector<Elem> elems;        

    ////////////////////////////////////////////////////////////////////////////
    // Heap operation helpers
    ////////////////////////////////////////////////////////////////////////////
    
    pair<int, int> children(int parent) {
        int lhs = 2*parent+1;
        int rhs = 2*parent+2;
        return make_pair(lhs, rhs);
    }
        
    int parent(int child) {
        if (child == 0) return 0;  // invalid really
        return ((child-1)/2);
    }        

    
    void bubbleUp(int index) {
        while (index != 0) {
            int p = parent(index);
            if (elems[p].timestamp < elems[index].timestamp) {return;}
            
            int pkey = elems[p].key;
            int ikey = elems[index].key;                        
            
            std::swap(elems[p], elems[index]);
            key_to_index[pkey] = index;
            key_to_index[ikey] = p;
            
            index = p;
        }
    }
        
    void bubbleDown(int index) {
        while (1) {
            int index_key = elems[index].key;
            auto cs = children(index);
            if (cs.first >= elems.size()) {return;}
            int lhs_i = cs.first;
            int rhs_i = cs.second;
            int lhs_k = elems[lhs_i].key;
            int rhs_k = rhs_i >= elems.size() ? -1 : elems[rhs_i].key;
            
            int lhs_ts = elems[lhs_i].timestamp;
            int rhs_ts = rhs_i >= elems.size() ? std::numeric_limits<int>::max() : elems[rhs_i].timestamp;
            
            bool lhs_violated = elems[index].timestamp > lhs_ts;
            bool rhs_violated = elems[index].timestamp > rhs_ts;            
            if (!lhs_violated && !rhs_violated) {
                return;
            }

            if (lhs_violated && rhs_violated) {
                if (lhs_ts > rhs_ts) {
                    lhs_violated = false;
                } else {
                    rhs_violated = false;
                }
            }
            
            if (lhs_violated) {
                std::swap(elems[lhs_i], elems[index]);
                key_to_index[lhs_k] = index;
                key_to_index[index_key] = lhs_i;
                index = lhs_i;
            } else { // rhs_violated
                std::swap(elems[rhs_i], elems[index]);
                key_to_index[rhs_k] = index;
                key_to_index[index_key] = rhs_i;
                index = rhs_i;                
            }
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Heap operations
    ////////////////////////////////////////////////////////////////////////////        
        
    // removes the top of the heap
    void pop() {
        if (elems.size() == 0) return;
        int evict_key = elems[0].key;
        
        if (elems.size() == 1) {
            key_to_index.erase(evict_key);
            elems.pop_back();
            return;
        }
        
        int affected_key = elems.back().key;
        std::swap(elems[0], elems[elems.size()-1]);
        
        key_to_index[affected_key] = 0;
        key_to_index.erase(evict_key);
        elems.pop_back();
        
        bubbleDown(0);
    }
        
    // returns the key for the top of heap
    // does not perform any checks
    int top() {
        return elems[0].key;
    }
        
    // updates an existing key's timestamp, and maintains heap property.
    void update(int key, int timestamp) {
        int index = key_to_index[key];
        elems[index].timestamp = timestamp;
        bubbleDown(index);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    
public:
    LRUCache(int cap) {
        capacity = cap;
    }
    
    int get(int key) {
        if (key_to_val.find(key) == key_to_val.end()) return -1;
        int val = key_to_val[key];
        update(key, time++);
        return val;
    }
    
    void put(int key, int value) {
        if (key_to_val.find(key) != key_to_val.end()) {
            key_to_val[key] = value;
            update(key, time++);
            return;
        }
        
        // Need to evict
        if (key_to_val.size() == capacity) {
            int evict_key = top();            
            key_to_val.erase(evict_key);            
            pop();
            // fall through
        }
        
        elems.push_back({key, time++});
        key_to_val[key] = value;
        key_to_index[key] = elems.size()-1;
        bubbleUp(elems.size()-1);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
