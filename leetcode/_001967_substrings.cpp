class Solution {
    class Trie {
        struct TrieNode {
            bool ends = false;
            vector<TrieNode*> children;
            TrieNode() {children = vector<TrieNode*>(26, nullptr);}
            ~TrieNode() {for (TrieNode* n : children) {delete n;}}
        };
        
      public:
        Trie(const string& s) : str(s) {
            root = new TrieNode();
            for (int i=0; i<s.size(); i++) {
                insert(s.substr(i));
            }
        }
        ~Trie() { delete root; }
        
        bool hasSubstr(const string& needle) {
            if (needle.size() > str.size()) return false;
            if (needle.size() == 0) return true;
            TrieNode* node = root;
            int n_ptr=0;
            while (n_ptr < needle.size()) {
                int index = needle[n_ptr] - 'a';
                if (node->children[index] == nullptr) return false;
                node = node->children[index];
                n_ptr++;
            }
            return true;
        }
      private:
        void insert(const string& word) {
            int w_ptr=0;
            TrieNode* node = root;
            while (w_ptr < word.size()) {
                int index = word[w_ptr] - 'a';
                if (node->children[index] == nullptr) {
                    node->children[index] = new TrieNode();
                }
                node = node->children[index];
                w_ptr++;
            }
            node->ends = true;
        }
        const string str;
        TrieNode* root = nullptr;
    };
public:
    // O(n*m) time, O(m*m) space.
    int numOfStrings(vector<string>& patterns, string word) {
        Trie trie(word);
        int count=0;
        for (const string& word : patterns) {
            if (trie.hasSubstr(word)) { count++; }
        }
        return count;
    }
};
