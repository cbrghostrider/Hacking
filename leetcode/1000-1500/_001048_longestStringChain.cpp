class Solution {
    struct Node {
        vector<int> children;  // the children nodes, which are predecessor words for this node
    };
    vector<Node*> nodes;     // the index within nodes corresponds to index within words
    Node* source = nullptr;  // special pseudo source node that connects to all nodes, used for dfs start
    
    // Map word to its node number.
    unordered_map<string, int> word_to_node;
    
    // Maps length to a set of words of that len.
    unordered_map<int, unordered_set<string>> len_to_words;
    
    unordered_map<Node*, int> visited;
    
    int dfs(Node* node) {
        if (visited[node] != 0) return visited[node];
        
        int max=0;
        for (int i=0; i<node->children.size(); i++) {
            int child = node->children[i];
            int my_len = 1 + dfs(nodes[child]);
            if (my_len > max) {max = my_len;}
        }
        
        visited[node] = max;
        return max;
    }
    
public:
    // Algorithm does 2 things:
    // 1. Build child relationships.
    // 2. Do a DFS from the pseudo source.
    //
    // #2 runtime is O(n), where n is the number of nodes = number of words.
    // #1 runtime is O(n*m) where m is length of each word. 
    // Actually probably O(n*m*m) because inner loop has string concat.
    //
    // Overall runtime there is O(n*m*m).
    int longestStrChain(vector<string>& words) {
        source = new Node();
        
        for (int i=0; i<words.size(); i++) {
            word_to_node[words[i]] = i;
            len_to_words[words[i].size()].insert(words[i]);
            nodes.push_back(new Node());
            source->children.push_back(i);
        }
        
        // Find children relationships.
        for (int i=0; i<words.size(); i++) {
            const string& word = words[i];
            int node = word_to_node[word];
            int len = word.size();
            if (len == 1) continue;
            
            for (int k=0; k<len; k++) {
                
                string ss = (k == 0     ? "" : word.substr(0, k)) + 
                            (k == len-1 ? "" : word.substr(k+1));
                
                auto iter = len_to_words[len-1].find(ss);
                if (iter != len_to_words[len-1].end()) {
                    const string& pred = *iter;
                    nodes[node]->children.push_back(word_to_node[pred]);
                }
            }
        }
        
        auto& v = visited;
        int max = dfs(source);
        return (max);
    }
};
