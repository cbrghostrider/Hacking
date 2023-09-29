class RLEIterator {
    vector<int> encoding;
    int cur_ptr=0;
    int cur_count=0;
    
    // gives how many elems exist for current encoding
    int elems() {
        if (cur_ptr >= encoding.size()) return 0;
        return encoding[cur_ptr] - cur_count;
    }
    
    void toNextElem() {
        cur_ptr += 2;
        cur_count=0;        
    }
    
public:
    RLEIterator(vector<int>& enc) {
        for (int i=0; i<enc.size(); i+=2) {
            if (enc[i] == 0) continue;
            encoding.push_back(enc[i]);
            encoding.push_back(enc[i+1]);
        }
    }
    
    int next(int n) {
        if (cur_ptr >= encoding.size()) return -1;  // all consumed
                
        int leftover=n;        
        while (elems() < leftover) {                
            leftover -= elems();
            toNextElem();
            if (cur_ptr >= encoding.size()) return -1;  // all consumed
        }
            
        int ret = encoding[cur_ptr+1];
        cur_count += leftover;
        
        if (cur_count == encoding[cur_ptr]) {
            toNextElem();
        }
        return ret;
    }
};

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator* obj = new RLEIterator(encoding);
 * int param_1 = obj->next(n);
 */
