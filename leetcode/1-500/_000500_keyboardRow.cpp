class Solution {
    std::unordered_set<char> first_row = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
    std::unordered_set<char> second_row = {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'};
    std::unordered_set<char> third_row = {'z', 'x', 'c', 'v', 'b', 'n', 'm'};
    
    bool withinRow(const unordered_set<char>& s, const string& word) {
        for (char c : word) {
            if (s.find(std::tolower(c)) == s.end()) return false;
        }
        return true;
    }
public:
    vector<string> findWords(vector<string>& words) {
        vector<string> ans;
        for (const string& word : words) {
            if (withinRow(first_row, word) || withinRow(second_row, word) || withinRow(third_row, word)) {
                ans.push_back(word);
            }
        }
        return ans;
    }
};
