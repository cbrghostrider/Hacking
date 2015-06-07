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
    //return value indicates if we delete upwards
    bool del(TrieNode*& nd, string& s, unsigned int lvl) {
        if (nd == NULL) return false; //no such word exists
        if (lvl == s.length()) {
            nd->Present(false); 
            for (int i=0; i<NUM_LETTERS; i++) {
                if ((*nd)[i]) { //children exist
                    return false;
                }
            }
            //no children exist
            if (lvl != 0) {
                delete nd;
                nd = NULL;
            }
            return true; //continue the cycle upwards
        }
        bool ret = del((*nd)[s[lvl]], s, lvl+1);
        if (ret == false) return false;  //no need to delete anything else
        if (nd->Present()) return false; //no need to delete anything else
        for (int i=0; i<NUM_LETTERS; i++) {
            if ((*nd)[i]) { //children exist
                return false;
            }
        }
        if (lvl != 0) { //don't delete root please
            delete nd;
            nd = NULL;
        }
        return true; //continue the cycle
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
    
    //removes a word from the trie
    void remove (string s) {
        del(root, s, 0);
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

class Solution {
    Trie trie;
    vector<string> retval;
    
    bool onBoard(vector<vector<char>>& board, int r, int c) {
        return (r >= 0 && c >= 0 && r < board.size() && c < board[0].size());
    }
    
    void traverse(vector<vector<char>>& board, vector<vector<bool>>& marks, string& sofar, int r, int c) {
        sofar = sofar + string(1, board[r][c]);
        if (!trie.startsWith(sofar)) {
            sofar.pop_back();
            return;
        }
        if (trie.search(sofar))  {
            retval.push_back(sofar);
            trie.remove(sofar);
        }
        marks[r][c] = true;
        if (onBoard(board, r, c+1) && !marks[r][c+1]) traverse(board, marks, sofar, r, c+1);
        if (onBoard(board, r+1, c) && !marks[r+1][c]) traverse(board, marks, sofar, r+1, c);
        if (onBoard(board, r-1, c) && !marks[r-1][c]) traverse(board, marks, sofar, r-1, c);
        if (onBoard(board, r, c-1) && !marks[r][c-1]) traverse(board, marks, sofar, r, c-1);
        sofar.pop_back();
        marks[r][c] = false;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (board.size() == 0 || board[0].size() == 0 || words.size() == 0) return vector<string>();
        
        for (string& word : words) trie.insert(word);
        
        for (int r=0; r<board.size(); r++) {
            for (int c=0; c<board[0].size(); c++) {
                vector<vector<bool>> marks(board.size(), vector<bool>(board[0].size(), false));
                string start = "";
                traverse(board, marks, start, r, c);
            }
        }
        return retval;
    }
};
