class Solution {
public:
    string removeVowels(string s) {
        string ans;
        for (char ch : s) {
            if (ch != 'a' && ch != 'e' && ch != 'i' && ch != 'o' && ch != 'u') {
                ans.push_back(ch);
            }
        }
        return ans;
    }
};
