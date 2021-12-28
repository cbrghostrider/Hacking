class Solution {
public:
    // 
    // Ugh... ugly.. but works, and I don't want to re-write it.
    // Should have either done char-by-char, or used regex...
    //
    vector<string> removeComments(vector<string>& source) {
        int s_ptr=0;
        bool in_block_comment = false;
        string carryover;   // partial line match of the same line carried over iterations
        
        vector<string> ans;
        auto addLine = [&s_ptr, &ans, &carryover](const string& l) {            
            if (!l.empty()) ans.push_back(l);
            s_ptr++;
            carryover.clear();
        };
        
        while (s_ptr < source.size()) {
            string& line = source[s_ptr];   
            string match = in_block_comment ? "*" : "/";
            int pos=line.find_first_of(match);
            
            if (pos == string::npos || pos == line.size()-1) {
                if (!in_block_comment) {
                    addLine(carryover + line);
                } else {
                    // if (!carryover.empty()) addLine(carryover);  
                    // else s_ptr++;
                    s_ptr++;
                }
                continue;
            }
            
            if (line[pos] == '/') {                            
                if (line[pos+1] == '/') {                      // found "//"
                    addLine(carryover + line.substr(0, pos));
                } else if (line[pos+1] == '*') {               // found "/*"
                    carryover += line.substr(0, pos);
                    line = pos+2 == line.size() ? "" : line.substr(pos+2);
                    in_block_comment = true;                    
                } else {                                       // can match comment later in line
                    carryover += line.substr(0, pos+1);
                    line = line.substr(pos+1);                 // re-parse
                }                                                
            } else if (line[pos] == '*') { 
                if (line[pos+1] != '/') {                      // this is not "*/"
                    if (!in_block_comment) {
                        carryover += line.substr(0, pos+2);                                       
                    }
                    line = pos+1 == line.size() ? "" : line.substr(pos+1);  // re-parse
                } else {                                       // found "*/"                                    
                    in_block_comment = false;
                    line = pos+2 == line.size() ? "" : line.substr(pos+2);  // re-parse
                }
            } 
        }        
        return ans;
    }
};
