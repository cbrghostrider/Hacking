// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
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
        return (get((*nd)[s[lvl]], s, lvl+1));
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

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");


