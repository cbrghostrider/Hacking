class Solution {
public:
    // Solution without using a trie.
    vector<vector<int>> indexPairs1(string text, vector<string>& words) {
        vector<vector<int>> coords;
        for (const string& word : words) {
            size_t pos = 0;
            while (pos != string::npos && (pos + word.size()-1) < text.size()) {
                pos = text.find_first_of(word[0], pos);
                if (pos == string::npos || (text.size() - pos) < word.size()) {
                    break;
                }
                bool matches = true;
                for (int ptr=0; ptr<word.size(); ptr++) {
                    if (word[ptr] != text[pos + ptr]) {
                        matches = false;
                        break;
                    }
                }
                
                if (matches)  {coords.push_back({static_cast<int>(pos), 
                                                 static_cast<int>(pos+word.size()-1)}); }
                pos++;
            }
        }
        std::sort(coords.begin(), coords.end(), [](const std::vector<int>& left, const std::vector<int>& right) -> bool {
            if (left[0] != right[0]) {
                return left[0] < right[0];
            }
            return left[1] < right[1];
        });
        return coords;
    }
    
    // Solution using a trie. 
    // Store the words (needles) in the trie.
    // Traverse the trie for each position in haystack to find how many needles are there.
    struct TrieNode {
        vector<TrieNode*> children;
        bool end = false;
        TrieNode() {
            children = vector<TrieNode*>(26, nullptr);
        }
        ~TrieNode() {
            for (TrieNode* child : children) {delete child;}
        }
    };
    TrieNode *root = nullptr;
    
    void insertInTrie(TrieNode* root, const string& word) {
        TrieNode *curr = root;
        for (int i=0; i<word.size(); i++) {
            char c = word[i];
            TrieNode *next = curr->children[std::tolower(c) - 'a'];
            if (next == nullptr) {
                curr->children[std::tolower(c) - 'a'] = next = new TrieNode();
            }
            curr = next;
        }
        curr->end = true;
    }
    
    vector<vector<int>> indexPairs(string text, vector<string>& words) {
        root = new TrieNode();
        for (const string& word : words) {
            insertInTrie(root, word);
        }
        
        vector<vector<int>> ans;
        for (int i=0; i<text.size(); i++) {
            TrieNode *node = root;
            for (int j=i; j<text.size(); j++) {
                char c = text[j];
                node = node->children[std::tolower(c) - 'a'];
                if (node == nullptr) break;
                if (node->end) {ans.push_back({i, j});}
            }
        }
        std::sort(ans.begin(), ans.end(), [](const std::vector<int>& left, const std::vector<int>& right) -> bool {
            if (left[0] != right[0]) {
                return left[0] < right[0];
            }
            return left[1] < right[1];
        });
        delete root;
        return ans;
    }
};
