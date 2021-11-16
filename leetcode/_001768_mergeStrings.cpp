class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string ans;
        int p1=0, p2=0;
        while (p1 < word1.size() && p2 < word2.size()) {
            ans.push_back(word1[p1++]);
            ans.push_back(word2[p2++]);
        }
        if (p1 < word1.size()) ans += word1.substr(p1);
        if (p2 < word2.size()) ans += word2.substr(p2);
        return ans;
    }
};
