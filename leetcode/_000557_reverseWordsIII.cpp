class Solution {
    // inclusive of [start, end]
    void reverseInPlace(string& s, int start, int end) {
        if (start >= end) return;
        int mid = (start+end)/2;
        for (int i=start, c=0; i<=mid; i++, c++) {
            std::swap(s[i], s[end-c]);
        }
    }
    
public:
    string reverseWords(string s) {
        int s_ptr = 0;
        while (s_ptr < s.size()) {
            size_t spc = s.find_first_of(" ", s_ptr);
            if (spc == string::npos) {
                reverseInPlace(s, s_ptr, s.size()-1);
                break;
            }
            reverseInPlace(s, s_ptr, spc-1);
            s_ptr = spc + 1;
        }
        return s;
    }
};
