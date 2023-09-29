class Solution {
public:
    bool checkOnesSegment(string s) {
        bool foundSeg = false;
        char prev='0';
        for (char ch : s) {
            if (ch == '1' && prev == '0') {
                if (foundSeg) return false;
                foundSeg = true;
            }
            prev = ch;
        }
        return true;
    }
};
