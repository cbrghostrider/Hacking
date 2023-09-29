class CombinationIterator {
    string chars;
    vector<int> indices;
    
    // bumps given index, and returns the new val at it
    int bump(int index) {
        int new_val = indices[index]+1;
        if (new_val == chars.size()-index && index != indices.size()-1) {
            new_val = bump(index+1);
            new_val = (new_val == chars.size()) ? new_val : new_val+1;
        }        
        indices[index] = new_val;
        return new_val;
    }
    
public:
    CombinationIterator(string characters, int combinationLength) {
        chars = characters;
        indices = vector<int>(combinationLength, 0);
        int val=0;
        for (int i=indices.size()-1; i>=0; i--) {
            indices[i] = val++;
        }
    }        
    
    string next() {
        if (!hasNext()) return "";
        
        string me;
        for (int ind : indices) {
            me.push_back(chars[ind]);
        }
        std::reverse(me.begin(), me.end());
        
        bump(0);        
        return me;
    }
    
    bool hasNext() {
        return (indices[0] != chars.size());
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
