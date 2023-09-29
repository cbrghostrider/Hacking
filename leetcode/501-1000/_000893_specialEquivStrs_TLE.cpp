class Solution {
    
    // Note that odd letters can never be in even positions, and vice versa.
    // Also all even letters can be rearraged among themselves willy-nilly (and so for odd).
    // The key insight is, if the following conditions hold for s1, s2, then they are special equiv:
    // 1. Same number of same letters in evens group. [comparing s1 and s2]
    // 2. Same number of same letters in odds group. [comparing s1 and s2]
    
    struct Info {
        unordered_map<char, int> odds;
        unordered_map<char, int> evens;
    };
    
    unordered_map<string, Info> mappings;
    
    Info getMappings(const string& s) {
        if (mappings.find(s) != mappings.end()) return mappings[s];
        Info info;
        for (int i=0; i<s.size(); i++) {
            if (i%2 == 0) {
                info.evens[s[i]]++;
            } else {
                info.odds[s[i]]++;
            }
        }
        mappings[s] = info;
        return info;
    }
    
    bool areSpecialEquiv(const string& s1, const string& s2) {
        Info s1_map = getMappings(s1);
        Info s2_map = getMappings(s2);
        if (s1_map.evens.size() != s2_map.evens.size()) return false;
        if (s1_map.odds.size() != s2_map.odds.size()) return false;
        
        for (const auto& kv : s1_map.evens) {
            if (s2_map.evens[kv.first] != kv.second) return false;
        }
        for (const auto& kv : s1_map.odds) {
            if (s2_map.odds[kv.first] != kv.second) return false;
        }
        return true;
    }
    
public:
    int numSpecialEquivGroups(vector<string>& words) {
        unordered_map<int, string> group_to_string;  // an example string that maps to this group
        
        int max=1;
        int group=0;
        for (string word : words) {
            bool group_found = false;
            for (const auto& kv : group_to_string) {
                if (areSpecialEquiv(word, kv.second)) {
                    group_found = true;
                    break;
                }
            }
            if (!group_found) {
                group_to_string[group] = word;
                group++;
            }
        }
        return group_to_string.size();
    }
};
