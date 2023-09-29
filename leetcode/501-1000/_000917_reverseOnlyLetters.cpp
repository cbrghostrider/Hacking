class Solution {
    bool isAlpha(char c) {
        return (alpha.find_first_of(std::string(1, c)) != string::npos);
    }
    string alpha;
public:
    string reverseOnlyLetters(string s) {
        for (char c='a'; c<='z'; c++) { alpha.push_back(c); }
        for (char c='A'; c<='Z'; c++) { alpha.push_back(c); }
        
        int left=0, right=s.size()-1;
        while (left < right) {
            while (left < right && !isAlpha(s[left])) left++;
            while (left < right && !isAlpha(s[right])) right--;
            if (left < right) {std::swap(s[left++], s[right--]);}
        }
        return s;
    }
};
