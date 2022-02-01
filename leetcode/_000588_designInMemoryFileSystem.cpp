class FileSystem {
    
    struct TrieNode {
        bool ends=false;      // a dir or path name ends here
        bool is_dir = false;  // if it ends, is it dir or path
        map<char, TrieNode*> children;
    };
    
    TrieNode* root = nullptr;
    
    // Will be called only after all dirs etc. for this path are created
    void addToTrie(const string& str, bool is_dir=false) {
        int s_ptr=0;
        TrieNode* node = root;
        
        while (s_ptr < str.size()) {
            if (node->children.find(str[s_ptr]) == node->children.end()) {
                node->children[str[s_ptr]] = new TrieNode();
            }
            node = node->children[str[s_ptr]];
            if (s_ptr < str.size()-1 && str[s_ptr+1] == '/') {
                node->ends = true;
                node->is_dir = true;
                dirs.insert(str.substr(0, s_ptr+1));
            }
            if (s_ptr == str.size()-1) {
                node->ends = true;                
                if (is_dir) {
                    node->is_dir = true;
                    dirs.insert(str);
                }
            }
            s_ptr++;
        }
    }
    
    TrieNode* find(const string& str) {
        int s_ptr=0;
        TrieNode* node = root;
        
        while (s_ptr < str.size()) {
            if (node->children.find(str[s_ptr]) == node->children.end()) {
                return nullptr;
            }
            node = node->children[str[s_ptr++]];
        }
        return node;
    }
    
    vector<string> walk(TrieNode* node, string& pstr, const string& orig) {
        vector<string> ans;
        for (const auto& kv : node->children) {            
            char ch = kv.first;
            if (ch == '/') continue;
            TrieNode* cnode = kv.second;
            pstr.push_back(ch);
            if (cnode->ends) {
                ans.push_back(pstr.substr(1));
            }
            const auto& rwalk = walk(cnode, pstr, orig);
            ans.insert(ans.end(), rwalk.begin(), rwalk.end());
            pstr.pop_back();
        }
        return ans;
    }
    
    vector<string> recursiveList(const string& str) {
        if (file_contents.find(str) != file_contents.end()) {
            // This is just a filename (not a directory).
            int pos = str.find_last_of("/");
            if (pos != string::npos) {return {str.substr(pos+1)};}
            return {str};
        }
        
        TrieNode* node = find(str);        
        if (node == nullptr || (str != "/" && node->children.find('/') == node->children.end())) {
            // non existent, or empty directory
            return {};
        }
        
        string rstr = str + str == "/" ? "" : "/";
        node = str == "/" ? node : node->children['/'];        
        return walk(node, rstr, str);
    }
    
    unordered_map<string, string> file_contents;
    unordered_set<string> dirs;
    
public:
    FileSystem() {
        root = new TrieNode();
        addToTrie("/", true);
    }
    
    vector<string> ls(string path) {
        return recursiveList(path);
    }
    
    void mkdir(string path) {
        addToTrie(path, true);
    }
    
    void addContentToFile(string filePath, string content) {
        addToTrie(filePath);
        file_contents[filePath] += content;
    }
    
    string readContentFromFile(string filePath) {
        if (file_contents.find(filePath) == file_contents.end()) return "";
        return file_contents[filePath];
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */
