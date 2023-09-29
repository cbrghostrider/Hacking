class ValidWordAbbr {
    unordered_map<string, unordered_set<string>> abbr_to_word;
    
    string getAbbr(const string& word) {
        if (word.size() <= 2) return word;
        int num = word.size()-2;
        string ret = string(1, word[0]) + to_string(num) + string(1, word.back());
        return ret;
    }
    
public:
    ValidWordAbbr(vector<string>& dictionary) {
        for (const string& word : dictionary) {
            string abbr = getAbbr(word);
            abbr_to_word[abbr].insert(word);  
        }
    }
    
    bool isUnique(string word) {
        string abbr = getAbbr(word);
        if (abbr_to_word.find(abbr) == abbr_to_word.end()) return true;
        return (abbr_to_word[abbr].find(word) != abbr_to_word[abbr].end() && abbr_to_word[abbr].size() == 1);
    }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */
