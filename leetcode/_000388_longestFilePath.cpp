class Solution {
public:
    int lengthLongestPath(string input) {
        stringstream ss(input);
        string line;
        vector<string> nest_stack;  // contains names of directories
        
        int longest=0;
        while (std::getline(ss, line)) {
            int pos = line.find_first_not_of("\t");
            string name = line.substr(pos == 0 || pos == string::npos ? 0 : pos);
            int my_nesting = (pos == 0 || pos == string::npos ? 0 : pos);
            
            if (my_nesting >= nest_stack.size()) {nest_stack.push_back(name);}
            else if (my_nesting == nest_stack.size()-1) {nest_stack.back() = name;}
            else {
                int limit = nest_stack.size()-my_nesting;
                for (int i=0; i<limit; i++) {
                    nest_stack.pop_back();
                }
                nest_stack.push_back(name);
            }
            
            int my_len = 0;
            for (string& sp : nest_stack) { my_len += sp.size(); }
            my_len += nest_stack.size()-1;  // for the '/' characters
            bool is_file = (name.find_first_of('.') != string::npos);
            if (is_file && my_len > longest) { 
                longest = my_len; 
            }
        }
        return longest;
    }
};
