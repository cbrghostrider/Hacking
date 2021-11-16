class Solution {
public:
    string reversePrefix(string word, char ch) {
        size_t pos = word.find_first_of(std::string(1, ch));
        if (pos == string::npos) return word;
        if (pos == word.size()-1) {
            std::reverse(word.begin(), word.end());
            return word;
        }
        string ans = word.substr(0, pos+1);
        std::reverse(ans.begin(), ans.end());
        ans += word.substr(pos+1);
        return ans;
    }
};
