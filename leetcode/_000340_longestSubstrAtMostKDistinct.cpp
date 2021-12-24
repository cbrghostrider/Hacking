class Solution {
public:
    // O(n) time, O(n) space. Two pointers.
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (s.size() == 0 || k == 0) return 0;
        
        unordered_map<char, int> counts;
        int s_ptr=0, e_ptr=0;
        int best=1;
        
        
        auto updateBest = [&best, &s_ptr, &e_ptr]() {
            int len = e_ptr-s_ptr+1;  
            best = std::max(best, len);
        };
        
        while (s_ptr < s.size()) {

            if (e_ptr < s.size() && 
                  (counts.size() < k || 
                   (counts.size() == k && counts.find(s[e_ptr]) != counts.end()))) {
                counts[s[e_ptr]]++; 
                updateBest();
                e_ptr++;                
            } else {
                counts[s[s_ptr]]--;
                if (counts[s[s_ptr]] == 0) {
                    counts.erase(s[s_ptr]);
                }
                s_ptr++;
            }
        }
        return best;         
    }
};
