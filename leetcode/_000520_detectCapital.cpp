class Solution {
    bool allLower(const string& s) {
        for (char ch : s) {
            if (!(ch >= 'a' && ch <='z')) return false;
        }
        return true;
    }
    bool allUpper(const string& s) {
        for (char ch : s) {
            if (!(ch >= 'A' && ch <='Z')) return false;
        }
        return true;
    }
public:
    bool detectCapitalUse(string word) {
        return (allLower(word) || allUpper(word) || 
                (allLower(word.substr(1)) && word[0] >= 'A' && word[0] <= 'Z'));
    }
};
