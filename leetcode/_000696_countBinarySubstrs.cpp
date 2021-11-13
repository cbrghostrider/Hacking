class Solution {
public:
    // O(n^2) time, O(1) space.
    int countBinarySubstrings2(string s) {
        int count=0;
        for (int s_ptr=0; s_ptr<s.size(); s_ptr++) {
            int flip_at = s_ptr;
            while (flip_at < s.size() && s[flip_at] == s[s_ptr]) flip_at++;
            int init_count = flip_at - s_ptr;
            if (flip_at + init_count > s.size()) continue;
            int flip_again = flip_at;
            while (flip_again < s.size() && s[flip_again] == s[flip_at]) flip_again++;
            if ((flip_again-flip_at) < (flip_at - s_ptr)) continue;
            count++;
        }
        return count;
    }
    
    // O(n) time, O(n) space.
    int countBinarySubstrings(string s) {
        // for each index, how long is a substr of consecutive x's starting at that index end
        unordered_map<int, int> index_lengths;
        
        int s_ptr = 0;
        while (s_ptr < s.size()) {
            int e_ptr = s_ptr;
            while (e_ptr < s.size() && s[s_ptr] == s[e_ptr]) { e_ptr++; }
            int num = e_ptr-s_ptr;
            for (; s_ptr<e_ptr; s_ptr++) {
                index_lengths[s_ptr] = num--;
            }
        }
        
        int count = 0;
        for (int s_ptr=0; s_ptr<s.size(); s_ptr++) {
            int sz = index_lengths[s_ptr];
            if (s_ptr + sz >= s.size()) break;
            if (index_lengths[s_ptr+sz] >= sz) count++;
        }
        return count;
    }
};
