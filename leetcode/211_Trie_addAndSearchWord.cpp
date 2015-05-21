// Slightly modified previous Trie implementation to account for 
// wildcard . matching

class TrieNode {
private:
#define NUM_LETTERS (26)
    bool present;
    TrieNode* nodes[NUM_LETTERS];
    int charToInd(char ch) {return (ch - 'a');}
public:
    TrieNode() : present(false), nodes() { for (int i=0; i<NUM_LETTERS; i++) nodes[i] = NULL; }
    ~TrieNode() { for (int i=0; i<NUM_LETTERS; i++) if (nodes[i]) delete nodes[i]; }
    bool Present() const {return present;}
    void Present(bool val) {present = val;}
    TrieNode*& operator[] (char ch) {return nodes[charToInd(ch)];}
    TrieNode*& operator[] (unsigned int i) {return nodes[i];}
};

class Trie {
    void put(TrieNode*& node, string& s, unsigned int lvl) {
        if (node == NULL) node = new TrieNode();
        if (lvl == s.length()) {
            node->Present(true);
        } else {
            put((*node)[s[lvl]], s, lvl+1);
        }
    }
    TrieNode* get(TrieNode *nd, string& s, unsigned int lvl) {
        if (nd == NULL) return NULL;
        if (lvl == s.length()) return nd;
        if (s[lvl] != '.') return (get((*nd)[s[lvl]], s, lvl+1));
        for (unsigned int i=0; i<NUM_LETTERS; i++) {
            if ((*nd)[i] != NULL) {
                TrieNode *fnd = get ((*nd)[i], s, lvl+1);
                if (fnd != NULL && fnd->Present()) return fnd;
            }
        }
        return NULL;
    }
public:
    Trie() {
        root = new TrieNode();
    }
    
    ~Trie() {
        delete root;
    }

    // Inserts a word into the trie.
    void insert(string s) {
        put(root, s, 0);
    }

    // Returns if the word is in the trie.
    bool search(string key) {
        TrieNode *node = get(root, key, 0);
        return (node == NULL ? false : node->Present());
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        return (get(root, prefix, 0) != NULL);
    }

private:
    TrieNode* root;
};

class WordDictionary {
    Trie trie;
public:
    WordDictionary() : trie() {}
    ~WordDictionary() {}

    // Adds a word into the data structure.
    void addWord(string word) {
        trie.insert(word);
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return trie.search(word);
    }
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");
