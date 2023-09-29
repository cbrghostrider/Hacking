class Solution {
    void populateSeg(string& s, int from, int to) {
        if (from < 0 || to < 0 || to >= s.size() || from > to) return;
        if (from == to) {
            char prev = (from == 0 ? 'a' : s[from-1]);
            char next = (to == s.size()-1 ? 'a' : s[to+1]);
            char pick = ' ';
            for (char ch='a'; ch <= 'z'; ch++ ) {
                if (ch != prev && ch != next) {
                    pick = ch;
                    break;
                }
            }
            s[from] = pick;
            return;
        }
        for (int i=from; i <= to; i++) {
            char prev = (i == 0 ? 'z' : s[i-1]);
            s[i] = (prev == 'z' ? 'a' : prev+1);
            prev = s[i];
        }
        if (to < s.size()-1 && s[to] == s[to+1]) {
            std::swap(s[to-1], s[to]);
        }
    }
public:
    string modifyString(string s) {
        int s_ptr=0;
        while (s_ptr < s.size() && s_ptr != string::npos) {
            int start = s.find_first_of("?", s_ptr);
            if (start == string::npos) { break; }
            
            int end = s.find_first_not_of("?", start);
            end = (end == string::npos ? s.size()-1 : end-1);
            
            populateSeg(s, start, end);
            s_ptr = end+1;
        }
        return s;
    }
};
