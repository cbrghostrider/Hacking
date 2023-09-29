class Solution {
public:
    string toLowerCase(string s) {
        for (char& ch : s) {
            ch = std::tolower(ch);
        }
        return s;
    }
};
