class Solution {
    string toNumStr(const string& word) {
        string ans;
        for (char ch: word) {
            ans += std::to_string(ch-'a');
        }
        return ans;
    }
public:
    bool isSumEqual(string firstWord, string secondWord, string targetWord) {
        string num1Str = toNumStr(firstWord);
        string num2Str = toNumStr(secondWord);
        string tgtStr = toNumStr(targetWord);
        long long num1 = std::stoll(num1Str);
        long long num2 = std::stoll(num2Str);
        long long tgt = std::stoll(tgtStr);
        return (num1+num2 == tgt);
    }
};
