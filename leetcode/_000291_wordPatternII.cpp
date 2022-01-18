class Solution {
    
    bool usedAlready(unordered_map<char, string>& mapping, const string& str) {
        for (const auto& kv : mapping) {
            if (kv.second == str) return true;
        }
        return false;
    }
    
    // called recursively to check for match.
    // at any point in time:
    // pindex index in pattern is being processed
    // sindex index is the next free thing in index
    // all the letters before pindex have been assigned using "mapping"
    // 
    // Exhaustive search using backtracking.
    bool match(const string& s, int sindex, const string& pattern, int pindex, 
               unordered_map<char, string> mapping) {
        if (pindex == pattern.size()) { 
            // If I made it this far, I matched properly if there's nothing left
            return sindex == s.size(); 
        }
        if (sindex >= s.size()) {
            // I got nothing left to give
            return false;
        }
        
        char todo = pattern[pindex];
        if (mapping.find(todo) != mapping.end()) {
            // I have to try and force match this
            if (mapping[todo].size() + sindex > s.size()) {
                return false;
            }
            if (s.substr(sindex, mapping[todo].size()) != mapping[todo]) {
                return false;
            }

            pindex += 1;
            sindex += mapping[todo].size();
            return match(s, sindex, pattern, pindex, mapping);
        }
                
        int max_size = s.size()-sindex;
        
        for (int sz=1; sz<=max_size; sz++) {
            unordered_map<char, string> new_map = mapping;
            string new_str = s.substr(sindex, sz);
            if (usedAlready(mapping, new_str)) continue;  // must be bijective
            new_map[pattern[pindex]] = new_str;
            int new_pindex = pindex+1;
            int new_sindex = sindex + sz;
            bool recurse = match(s, new_sindex, pattern, new_pindex, new_map);
            if (recurse) {return true;}
        }
        
        return false;
    }
    
public:
    bool wordPatternMatch(string pattern, string s) {        
        unordered_map<char, string> mappings;        
        bool possible = match(s, 0, pattern, 0, mappings);
        return possible;
    }
};
