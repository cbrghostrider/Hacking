class Solution {
public:
    string sortSentence(string s) {
        string ans;
        stringstream ss(s);
        string str;
        unordered_map<int, string> words;
        while (getline(ss, str, ' ')) {
            size_t pos = str.find_first_of("0123456789");
            string num = str.substr(pos);
            if (pos == string::npos) return "Error: Malformed input.";
            string word = str.substr(0, pos);
            words[std::stoi(num)] = word;
        }
        for (int i=1; i<words.size(); i++) {
            ans += words[i] + " ";
        }
        ans += words[words.size()];
        return ans;
    }
};
