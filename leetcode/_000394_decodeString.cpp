class Solution {
    const string digits = "0123456789";
    
    // decodes a single rule (possibly recursively)
    // updates s_ptr accordingly
    string decodeSingle(const string& s, int& s_ptr) {
        if (std::isalpha(s[s_ptr])) {
            // very simple case, single letter
            return string(1, s[s_ptr++]);
        }
        
	// sub will be repeated num times to get ret
        string ret;
        string sub;
        int num=0;  
             
        int pos = s.find_first_not_of(digits, s_ptr);
        num = std::stoi(s.substr(s_ptr, pos - s_ptr));
        s_ptr = pos + 1;  // fastforward to after the '['
            
        int num_pos = s.find_first_of(digits, s_ptr);
        int close_pos = s.find_first_of("]", s_ptr);
        
        if (num_pos == string::npos || close_pos < num_pos) {  
            // this is a simple string, no recursion involved
            sub = s.substr(s_ptr, close_pos - s_ptr);
            s_ptr = close_pos + 1;
        } else {
            // we have to recurse unfortunately
            string my_sub = s.substr(s_ptr, num_pos - s_ptr);
            s_ptr = num_pos;
            string recursed;
            while (s[s_ptr] != ']') {  
                // the recursed part itself might have to be serially called
		// or further recursed (handled in that function's call stack).
                // e.g. 3[a2[c]2[b]2[d]] or 3[a2[c]2[b[2[c[2[d]]]]]4[e]]
                recursed += decodeSingle(s, s_ptr);
            }
            s_ptr += 1;  // to account for the ']'
            sub = my_sub + recursed;
        }
        
        for (int i=0; i<num; i++) {
            ret += sub;
        }
        return ret;
    }
    
public:
    string decodeString(string s) {
        string ret;
        int s_ptr=0;  // always points to next thing to be consumed
        while (s_ptr < s.size() && s_ptr != string::npos) {
            ret += decodeSingle(s, s_ptr);
        }
        return ret;
    }
};
