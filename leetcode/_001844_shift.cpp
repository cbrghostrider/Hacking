class Solution {
public:
    string replaceDigits(string s) {
        if (s.size() <= 1) return s;
        auto shift = [](char ch, int i) {return ch + i;};
        for (int i=1; i<s.size(); i+=2) {
            s[i] = shift(s[i-1], std::stoi(std::string(1, s[i])));
        }
        return s;
    }
};
