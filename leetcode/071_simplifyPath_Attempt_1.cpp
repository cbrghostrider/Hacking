//works fine, for corner cases as well
//need to make code more concise though in a future attempt!
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
    
    //initially tokenize the string into "../" and NOT-"../" tokens
    //then treat a NOTDotDotSlash-followed-by-DotDotSlash as a NOP
    void simplifyDotDotSlash(string& path) {
        if (path.length() == 0) return;
        
        vector<string> stack;
        while (path.length()) {
            if (path.substr(0, 3) == "../") {
                stack.push_back("../");
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
        
        int dotdotslash = 0; //records excess "../"
        string final;        //the final output string
        string topstr = stack.back(); stack.pop_back();
        while (!stack.empty()) {
            string nextstr = stack.back(); stack.pop_back();
            if (topstr == "../" && nextstr == "../") {
                dotdotslash++;
            } else if (topstr == "../" && nextstr == "/") { //topstr eaten by nextstr
                if (dotdotslash) {
                    dotdotslash = 0; //all accumulated "../" will be eaten as well
                }
                topstr = nextstr;
            } else if (topstr == "../" && nextstr != "../")  {//nextstr and topstr annihilate
                if (dotdotslash) {
                    dotdotslash--;
                } else if (stack.empty() ) {
                    topstr = "";
                    break;
                } else {
                    topstr = stack.back(); stack.pop_back();
                }
            } else if (topstr != "../") {
                final = topstr + final;
                topstr = nextstr;
            }
        }
        path = topstr + final;
        while (dotdotslash--) {
            path = "../" + path;
        }
    }
    
public:
    string simplifyPath(string path) {
        if (path.length() == 0) return path;
        
        path += "/"; //add trailing slash
        
        bool change=true;
        while (change) {
            string orig = path;
            change = false;
            
            eatDotSlash(path);
        
            simplifySlashes(path);    
            
            simplifyDotDotSlash(path);
            
            if (orig != path) change = true;
        }
        
        if (path.length() > 1 && path[path.size()-1] == '/') path.pop_back();
        if (path.length() == 0) path = ".";
        return path;
    }
};
