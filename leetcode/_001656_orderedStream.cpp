class OrderedStream {
    int ptr = 0;
    vector<string> values;
    
    vector<string> retval() {
        vector<string> ret;
        while (ptr < values.size() && values[ptr] != "") {
            ret.push_back(values[ptr++]);
        }
        return ret;
    }
    
public:
    OrderedStream(int n) {
        values = vector<string>(n, "");
    }
    
    vector<string> insert(int idKey, string value) {
        idKey -= 1;  // make 0 indexed
        values[idKey] = value;
        return retval();
    }
};

/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(idKey,value);
 */
