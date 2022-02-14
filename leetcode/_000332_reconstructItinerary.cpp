class Solution {
    const string SOURCE = "JFK";
    int NUM;
    map<string, set<pair<string, int>>> adj_list;
    
    vector<string> path;
    
    unordered_set<int> used;
    
    bool traverse(string curr) {
        if (used.size() == NUM) return true;
        
        for (const auto& kv : adj_list[curr]) {
            int edge_num = kv.second;
            string city = kv.first;
            
            // This edge already used.
            if (used.find(edge_num) != used.end()) continue;
            
            // Try it.
            used.insert(edge_num);
            path.push_back(city);
            if (traverse(city)) return true;
                
            // Untry it (backtrack).
            used.erase(edge_num);
            path.pop_back();
        }
        
        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        NUM = tickets.size();
        
        for (int i=0; i<tickets.size(); i++) {
            const auto& edge = tickets[i];
            adj_list[edge[0]].insert({edge[1], i});
        }
        
        path.push_back(SOURCE);
        traverse(SOURCE);
        
        return path;
    }
};
