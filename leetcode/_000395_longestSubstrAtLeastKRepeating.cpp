class Solution {
    
    int longest(const string& s, int start, int end, int k) {
        unordered_map<char, int> counts;
        for (int i=start; i<=end; i++) {counts[s[i]]++;}
        
        bool qualifies=true;
        for (const auto& kv : counts) {
            if (kv.second < k) {qualifies = false; break;}
        }
        if (qualifies) return end-start+1;
        
        int s_ptr=start, best=0;
        
        while (s_ptr <= end) {
            while (s_ptr <= end && counts[s[s_ptr]] < k) {s_ptr++;}
            if (s_ptr > end) break;
            
            int e_ptr=s_ptr;
            while (e_ptr <= end && counts[s[e_ptr]] >= k) {
                e_ptr++;
            }
            int cand = longest(s, s_ptr, e_ptr-1, k);
            best = std::max(best, cand);
            
            s_ptr = e_ptr;
        }
        
        return best;
    }
    
public:
    int longestSubstring(string s, int k) {        
        return longest(s, 0, s.size()-1, k);
    }
};
