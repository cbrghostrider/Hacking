class Solution {
public:
    // O(n) time, O(n+k) space; k = number of mappings, n for the answer string.
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mappings;
        for (const auto& kv : knowledge) {
            mappings[kv[0]] = kv[1];
        }
        
        string ret;        
        int s_ptr=0;
        while (s_ptr < s.size() && s_ptr != string::npos) {
            int pos = s.find_first_of("(", s_ptr);
            int len = pos == string::npos ? s.size()-s_ptr : pos-s_ptr;
            ret += s.substr(s_ptr, len);
            if (pos == string::npos) {break;}
            
            s_ptr = pos+1;
            pos = s.find_first_of(")", s_ptr);
            len = pos == string::npos ? s.size()-s_ptr : pos-s_ptr;
            string key = s.substr(s_ptr, len);
                        
            string value = "?";
            if (mappings.find(key) != mappings.end()) {
                value = mappings[key];
            }
            ret += value;
            
            if (pos == string::npos) {break;}  // erroneous input
            s_ptr = pos+1;
        }
        return ret;
    }
};
