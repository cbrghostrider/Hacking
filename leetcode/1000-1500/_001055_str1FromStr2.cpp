class Solution {
public:
    // O(mn) time, O(m) space.
    int shortestWay(string source, string target) {
        unordered_set<char> s;
        for (char ch : source) {s.insert(ch);}
        for (char ch : target) {
            if (s.find(ch) == s.end()) return -1;
        }
        int used=1, s_ptr=0, t_ptr=0;
        while (t_ptr < target.size()) {
            if (source[s_ptr] == target[t_ptr]) { 
                t_ptr++; 
                if (t_ptr == target.size()) { break; }
            }
            s_ptr++;
            if (s_ptr == source.size()) {
                used++;
                s_ptr=0;
            }
        }
        return used;
    }
};
