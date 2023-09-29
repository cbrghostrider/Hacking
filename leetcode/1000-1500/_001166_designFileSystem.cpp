class FileSystem {
    unordered_map<string, int> vals;
    
public:
    FileSystem() {}            
    
    bool createPath(string path, int value) {        
        int pos = path.find_last_of("/");        
        if (pos != string::npos && pos != 0) {
            string parent = path.substr(0, pos);            
            if (vals.find(parent) == vals.end()) return false;
        }
        if (vals.find(path) != vals.end()) return false;
        vals[path] = value;
        return true;        
    }
    
    int get(string path) {
        if (vals.find(path) == vals.end()) return -1;
        return vals[path];
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */
