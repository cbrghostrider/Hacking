class Solution {
public:
    string reverseVowels(string s) {
        const string vowels = "aeiou";
        int lp=0, rp=s.size()-1;
        while (lp<s.size() && rp >= 0 && lp<rp) {
            while (lp<s.size() && vowels.find(std::tolower(s[lp])) == string::npos) lp++;
            while (rp >= 0 && vowels.find(std::tolower(s[rp])) == string::npos) rp--;
            if (lp >= rp) break;
            std::swap(s[lp++], s[rp--]);
        }
        return s;
    }
};
