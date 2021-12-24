class Solution {
public:
    // O(n) time, O(m) space.
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) return {};
        
        unordered_map<char, int> counts, orig;
        for (char ch : p) {counts[ch]++;}
        orig = counts;  
        
        vector<int> ans;
        int s_ptr=0, e_ptr=0;  // e_ptr is the next thing to be examined
        while (e_ptr < s.size()) {            
            if (counts.find(s[e_ptr]) == counts.end()) {
                s_ptr = e_ptr = e_ptr+1;
                counts = orig;             
            } else if (counts[s[e_ptr]] == 0) {
                // not enough letters to remove
                counts[s[s_ptr]]++;
                s_ptr++;
            } else {        
                counts[s[e_ptr]]--;
                e_ptr++;
                if (e_ptr - s_ptr == p.size()) {
                    ans.push_back(s_ptr);
                }
            }
        }
        return ans;
    }
};
