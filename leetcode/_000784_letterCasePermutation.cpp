class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> ans;
        ans.push_back("");
        for (int i=0; i<s.size(); i++) {
            vector<string> temp;
            for (string word : ans) {
                temp.push_back(word + std::string(1, s[i]));
                if (s[i] != std::toupper(s[i])) {temp.push_back(word + std::string(1, std::toupper(s[i])));}
                if (s[i] != std::tolower(s[i])) {temp.push_back(word + std::string(1, std::tolower(s[i])));}
            }
            ans = temp;
        }
        return ans;
    }
};
