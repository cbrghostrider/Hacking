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
    string reverseStr(string s, int k) {
        int s_ptr=0, i=0;
        for (; i<s.size(); i += 2*k) {
            if ((i + k) >= s.size()) {
                reverseInPlace(s, i, s.size()-1);
            } else {
                reverseInPlace(s, i, i+k-1);
            }
        }
        return s;
    }
};
