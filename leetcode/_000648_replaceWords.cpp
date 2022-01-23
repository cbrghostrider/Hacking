class Solution {
    struct Node {        
        bool ends_here = false;  // a word ends here
        Node() {
            children = vector<Node*>(26, nullptr);
        }
        vector<Node*> children;
    };
    
    Node* trie = nullptr;
    
    void insert(const string& word) {
        Node* node = trie;
        for (int i=0; i<word.size(); i++) {
            char ch=word[i];
            Node* child = node->children[ch - 'a'];
            if (child == nullptr) {
                child = node->children[ch-'a'] = new Node();
            }
            node = child;
        }
        node->ends_here = true;  // the word ended
    }
    
    // walks the trie using word
    // if we find a prefix root, return prefix
    string walk(Node* node, const string& word, int ind) {
        if (ind >= word.size()) return word;  
        if (node->children[word[ind] - 'a'] == nullptr) return word;
        node = node->children[word[ind]-'a'];
        if (node->ends_here) {
            return word.substr(0, ind+1);
        }
        return walk(node, word, ind+1);
    }
    
public:
    // k = |word|
    // n = |dictionary|
    // m = |sentence|
    // O(n*k) time to build the trie.
    // O(m) time to check the entire sentence.
    // O(n*k + m) time overall, O(n*k) space overall.
    string replaceWords(vector<string>& dictionary, string sentence) {
        trie = new Node();
        
        for (const string& word : dictionary) {
            insert(word);
        }
        
        string ans;
        int s_ptr=0;
        while (s_ptr < sentence.size() && s_ptr != string::npos) {
            int pos = sentence.find_first_of(" ", s_ptr);
            int len = pos == string::npos ? sentence.size()-s_ptr : pos-s_ptr;
            string word = sentence.substr(s_ptr, len);
            
            string replace = walk(trie, word, 0);
            ans += replace + " ";
            
            if (pos == string::npos) { break; }
            s_ptr = pos+1;
        }
        
        ans.pop_back();  // last space
        return ans;
    }
};
