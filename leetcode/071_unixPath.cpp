class Solution {
    
    void eatDotSlash(string& path) {
        if (path.length() == 0) return;
        
        //eat leading "./" unless only "./" remains
        while (path.substr(0, 2) == string("./") && path.length() > 2 && path[2] != '/') {
            path = path.substr(2);
        }
        
        bool change = true;
        //change inline "/./" to "/"
        while (change) {
            string orig = path;
            change = false;
            
            size_t n = path.find("/./");
            if (n != string::npos) path = path.substr(0, n) + "/" + path.substr(n+3);
            
            if (orig != path) change = true;
        }
    }
    
    void simplifySlashes(string& path) {
        if (path.length() == 0) return;
        
        bool change = true;
        while (change) {
            string orig = path;
            change = false;
            
            size_t n = path.find("//");
            if (n != string::npos) path = path.substr(0, n) + "/" + path.substr(n+2);
            
            if (orig != path) change = true;
        }
    }
    
    void simplifyDotDotSlash(string& path) {
        if (path.length() == 0) return;
        
        vector<string> stack;
        while (path.length()) {
            if (path.substr(0, 3) == "../") {
                if (stack.empty() || stack.back() == "../") {
                    stack.push_back("../");
                } else if (stack.back() == "/")  {
                    ; // "/" will eat the "../"
                } else {
                    stack.pop_back(); //both will annihilate each other
                }
                path = path.substr(3);
            } else {
                size_t fst = path.find_first_of("/");
                if (fst == string::npos) {
                    stack.push_back(path);
                    path = "";
                } else {
                    stack.push_back(path.substr(0, fst+1));
                    path = path.substr(fst+1);
                }
            }
        }
        
        string final;
        while (!stack.empty()) {
            final = stack.back() + final;
            stack.pop_back();
        }
        path = final;
    }
    
public:
    string simplifyPath(string path) {
        if (path.length() == 0) return path;
        path += "/"; //add trailing slash
            
        eatDotSlash(path);
        simplifySlashes(path);    
        simplifyDotDotSlash(path);

        if (path.length() > 1 && path[path.size()-1] == '/') path.pop_back();
        if (path.length() == 0) path = ".";
        return path;     
    }
};
