class Solution {
public:
    // O(n) time, O(n) space.
    string reformat(string s) {
        string letters, digits;
        for (char ch : s) {
            if (std::isalpha(ch)) { letters.push_back(ch); } else {digits.push_back(ch);}
        }
        bool possible = (letters.size()     == digits.size()) || 
                        (letters.size() + 1 == digits.size()) || 
                        (letters.size()     == digits.size() + 1);
        if (!possible) return "";
        
        string ans;
        while (!letters.empty() && !digits.empty()) {
            ans.push_back(letters.back()); letters.pop_back();
            ans.push_back(digits.back()); digits.pop_back();
        }
        if (!letters.empty()) {ans.push_back(letters.back());}
        if (!digits.empty()) {ans = std::string(1, digits.back()) + ans;}
        return ans;
    }
};


