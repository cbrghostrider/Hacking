class Solution {
public:
    string makeFancyString(string s) {
        if (s.size() <= 2) return s;
        char ch1=s[0], ch2=s[1];
        string ans = s.substr(0, 2);
        for (int i=2; i<s.size(); i++) {
            if (!(ch1 == ch2 && ch2 == s[i])) {
                ans.push_back(s[i]);
                ch1 = ch2;
                ch2 = s[i];
            }
        }
        return ans;
    }
};
