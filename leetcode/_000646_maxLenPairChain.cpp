class Solution {
    
    // keys are all indices in pairs
    unordered_map<int, unordered_set<int>> adj_list;
    
    // cache of MAX path lengths, from index i in pairs to the pseudo dest
    unordered_map<int, int> cache;
    
    // longest length of chain ending in pair at index i
    vector<int> clen; 
    
    // traverse from index to end in pairs
    // end is guaranteed to be connected to everything
    int traverse(int index, int end) {
        if (cache.find(index) != cache.end()) {
            return cache[index];
        }
        
        int max_path=0;
        for (int neigh  : adj_list[index]) {
            int my_path = 1 + traverse(neigh, end);
            max_path = std::max(max_path, my_path);
        }
        
        cache[index] = max_path;
        return cache[index];
    }
    
public:
    
    // O(n^2) time, O(n) space.
    int findLongestChain(vector<vector<int>>& pairs) {
        
        std::sort(pairs.begin(), pairs.end(), [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            if (lhs[0] != rhs[0]) return lhs[0] < rhs[0];
            return lhs[1] < rhs[1];
        });
        
        pairs.insert(pairs.begin(), {-1005, -1005});  // pseudo source
        pairs.push_back({1005, 1005});  // pseudo destination      
        clen.push_back(0);
                
        // Build the graph
        for (int i=1; i<pairs.size(); i++) {
            int pred=0;  // the pseudo source
            
            // This code is the new way to do it.
            // It adds the node in exactly one place, which is the already existing longest chain.
            for (int j=0; j<i; j++) {
                if (pairs[j][1] < pairs[i][0] && clen[j] > clen[pred]) {
                    pred = j;
                }
            }
            adj_list[pred].insert(i);
            clen.push_back(clen[pred]+1);
            
            // Commented out code was the previous way to do it.
            // It added the node to every valid place that it could be added.
            /*
            for (int j=0; j<i; j++) {
                if (pairs[j][1] < pairs[i][0]) {
                    adj_list[j].insert(i);
                }                
            }
            */
        }
        
        int end = pairs.size()-1;  // the pseudo dest
        cache[end] = 0;
        
        int len = traverse(0, end);
        return len-1;  // remove start and end links, since those are pseudo
    }
};
