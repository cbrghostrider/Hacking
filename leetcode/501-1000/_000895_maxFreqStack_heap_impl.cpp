class FreqStack {
    struct Info {
        int val=-1;
        uint16_t freq=0;
        vector<uint16_t> seq;   
    };
    
    uint16_t seq=0;  // a monotonically increasing seq number to break ties properly
    vector<Info> container;  // implements a max-heap based on freq
    unordered_map<int, int> val_to_index;    
      
    bool exists(int index) {
        return (index >=0 && index < container.size());
    }
    
    pair<int, int> getChildren(int index) {
        return make_pair(2*index+1, 2*index+2);
    }    
    
    int getParent(int index) {
        if (index == 0) return -1;  // root!
        return ((index-1)/2);
    }
    
    // swaps them in the container
    // also maintains the bookkeeping info
    void heapSwap(int my_index, int other_index) {
        Info me=container[my_index];
        Info other=container[other_index];
        
        val_to_index[me.val] = other_index;
        val_to_index[other.val] = my_index;
        
        container[my_index] = other;
        container[other_index] = me;
    }
    
    // Perform bubble up, starting at index, moving upwards.
    void bubbleUp(int index) {
        if (index == 0) return;  // at root, done.
        int parent = getParent(index);
        
        Info& me = container[index];
        Info& my_parent = container[parent];
        if (me.freq > my_parent.freq) {
            heapSwap(index, parent);
            bubbleUp(parent);
        } else if (me.freq == my_parent.freq && me.seq.back() > my_parent.seq.back()) {
            // move the later pushed val
            heapSwap(index, parent);
            bubbleUp(parent);
        }        
    }
    
    // Perform bubble down, starting at index, moving downwards.
    void bubbleDown(int index) {
        Info& me = container[index];
        
        auto children = getChildren(index);
        if (!exists(children.first)) return;  // no left (therefore also no right) child
        
        bool right_violation = false, left_violation=false;
        Info right_child;
        if (exists(children.second)) {
            right_child = container[children.second];
            if (right_child.freq > me.freq) {right_violation = true;}
            if (right_child.freq == me.freq && right_child.seq.back() > me.seq.back()) {right_violation = true;}
        }
        Info& left_child = container[children.first];
        if (left_child.freq > me.freq) {left_violation = true;}
        if (left_child.freq == me.freq && left_child.seq.back() > me.seq.back()) {left_violation = true;}
        
        if (!left_violation && !right_violation) {return;}
        if (left_violation && right_violation) {
            if (left_child.freq > right_child.freq || 
                (left_child.freq == right_child.freq && left_child.seq.back() > right_child.seq.back())) {
                heapSwap(index, children.first);
                bubbleDown(children.first);
            } else {
                heapSwap(index, children.second);
                bubbleDown(children.second);                
            }
            return;
        }
        if (left_violation) {
            heapSwap(index, children.first);
            bubbleDown(children.first);            
            return;
        }
        heapSwap(index, children.second);
        bubbleDown(children.second);         
    }
    
    
public:
    FreqStack() {}            
    
    // O(log n) time.
    void push(int val) {   
        if (val_to_index.find(val) == val_to_index.end()) {
            container.push_back({val, 1, {seq++}});
            int index = container.size()-1;
            val_to_index[val] = index;
            bubbleUp(index);
            return;  
        } 
        int index = val_to_index[val];
        container[index].freq++;
        container[index].seq.push_back(seq++);
        bubbleUp(index);
    }
    
    // O(log n) time.
    int pop() {
        int index=0;  // root
        int ret = container[index].val;
        container[index].freq--;
        container[index].seq.pop_back();
        
        if (container[index].freq == 0) {
            container[index] = container.back();
            val_to_index[container.back().val] = index;
            container.pop_back();
            val_to_index.erase(ret);
            // fall through
        }
        
        bubbleDown(index);
        return ret;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
