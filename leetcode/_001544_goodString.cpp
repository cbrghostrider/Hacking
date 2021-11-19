class Solution {
public:
    string makeGood(string s) {
        string ans;
        for (char ch : s) {
            if (ans.empty()) {
                ans.push_back(ch);
            } else if (ans.back() != ch && 
                       ((ans.back() == std::toupper(ch)) || (ch == std::toupper(ans.back())))) {
                ans.pop_back();
            } else {
                ans.push_back(ch);
            }
        }
        return ans;
    }
};
