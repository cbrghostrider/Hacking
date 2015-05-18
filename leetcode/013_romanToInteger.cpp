class Solution {
    unordered_map<string, int> roman = {
        {"M", 1000}, {"CM", 900}, {"D", 500}, {"CD", 400}, 
        {"C", 100}, {"XC", 90}, {"L", 50}, {"XL", 40}, 
        {"X", 10}, {"IX", 9}, {"V", 5}, {"IV", 4}, {"I", 1}};
public:
    int romanToInt(string s) {
        if (s.length() == 0) return 0;
        if (s.length() == 1) return roman[s];
        string two = s.substr(0, 2);
        string rest;
        int thisNum=0;
        if (two == "CM" || two == "CD" || two == "XC" || two == "XL" || two == "IX" || two == "IV") {
            thisNum = roman[two];
            rest = s.substr(2);
        } else {
            thisNum = roman[s.substr(0, 1)];
            rest = s.substr(1);
        }
        return (thisNum + romanToInt(rest));
    }
};
