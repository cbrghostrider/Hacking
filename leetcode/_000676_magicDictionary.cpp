class MagicDictionary {
    unordered_set<string> original;           // the original words
    unordered_map<string, string> mutations;  // mutations of the original word
    unordered_set<string> exceptions;         // the original words that mutate to each other
public:
    MagicDictionary() {}
   
    // O(n*m) time to build.
    // O(n*m) space consumed.
    void buildDict(vector<string> dictionary) {
        for (const string& word : dictionary) {
            original.insert(word);
            for (int i=0; i<word.size(); i++) {
                string mutation = word;
                mutation[i] = '-';
                if (mutations.find(mutation) != mutations.end()) {
                    exceptions.insert(mutations[mutation]);
                    exceptions.insert(word);
                }
                mutations.insert({mutation, word});                    
            }
        }
    }
    
    // O(m) time to search.
    bool search(string searchWord) {
        if (exceptions.find(searchWord) != exceptions.end()) return true;
        if (original.find(searchWord) != original.end()) return false;
        for (int i=0; i<searchWord.size(); i++) {
            string str = searchWord;
            str[i] = '-';
            if (mutations.find(str) != mutations.end()) return true;
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
