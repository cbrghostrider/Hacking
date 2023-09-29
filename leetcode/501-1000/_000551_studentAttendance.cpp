class Solution {
public:
    bool checkRecord(string s) {
        int count=0;
        std::for_each(s.begin(), s.end(), [&count](char ch) {
            if (ch == 'A') count++;
        });
        if (count >= 2) return false;
        for (int i=2; i<s.size(); i++) {
            if (s[i-2] == 'L' && s[i-1] == 'L' && s[i] == 'L') return false;
        }
        return true;
    }
};
