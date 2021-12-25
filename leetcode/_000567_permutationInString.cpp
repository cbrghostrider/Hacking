class Solution {
    bool compare(const unordered_map<char, int>& m1, const unordered_map<char, int>& m2) {
        if (m1.size() != m2.size()) return false;
        for (const auto& kv : m1) {
            auto it = m2.find(kv.first);
            if (it == m2.end() || it->second != kv.second) return false;
        }
        return true;
    }
public:

    bool checkInclusion(string s1, string s2) {
        if (s2.size() < s1.size()) return false;
        
        unordered_map<char, int> freqs, check;
        for (char ch : s1) {freqs[ch]++;}
        
        int s_ptr=0, e_ptr=0;
        for (; e_ptr<s_ptr+s1.size(); e_ptr++) {
            check[s2[e_ptr]]++;
        }
        
        if (compare(freqs, check)) return true;
        while (e_ptr < s2.size()) {
            check[s2[s_ptr]]--;
            if (check[s2[s_ptr]] == 0) {
                check.erase(s2[s_ptr]);
            }
            s_ptr++;            
            check[s2[e_ptr]]++;
            e_ptr++;
            if (compare(freqs, check)) return true;
        }
        return false;
    }
};
