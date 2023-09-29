class Solution {
    vector<char> gchars = {'A', 'C', 'G', 'T'};
    unordered_set<string> genes;
    unordered_map<string, vector<string>> graph;
    
    void buildGraph(const string& gene) {
        vector<string> neighs;
        vector<string> recurse;
        
        for (int i=0; i<gene.size(); i++) {
            for (int c=0; c<gchars.size(); c++) {
                if (gchars[c] == gene[i]) continue;
                
                string mutation = gene;
                mutation[i] = gchars[c];
                if (genes.find(mutation) == genes.end()) continue;  // invalid mutation

                if (graph.find(mutation) == graph.end()) {
                    recurse.push_back(mutation);
                    graph[mutation] = {};
                }
                neighs.push_back(mutation);  // 1-edit to this mutation                
            }
        }
        graph[gene] = neighs;
        
        for (const string& gneigh : recurse) {
            buildGraph(gneigh);
        }
    }
    
public:
    
    // O(|bank|) = O(n) for buildGraph (gene.size() fixed at 8, gchars fixed at 4)
    // O(n) for BFS.
    // O(n) time overall, O(n) space overall.
    int minMutation(string start, string end, vector<string>& bank) {
        for (const string& gene : bank) {genes.insert(gene);}
        
        buildGraph(start);
        
        // perform a BFS
        unordered_set<string> visited;
        visited.insert(start);
        
        std::queue<pair<string, int>> q;
        q.push({start, 0});
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            if (elem.first == end) {return elem.second;}
            
            for (const string& neigh : graph[elem.first]) {
                if (visited.find(neigh) != visited.end()) continue;
                visited.insert(neigh);
                q.push({neigh, elem.second+1});
            }
        }
        return -1;        
    }
};
