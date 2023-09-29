// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    typedef unordered_set<int> Bucket;
    typedef vector<Bucket> AdjList;

    AdjList adjList;
    vector<bool> visited;
    vector<int> ccParent;
    
    void initialize(int n, vector<pair<int, int>>& edges) {
        visited  = vector<bool>(n, false);
        ccParent = vector<int>(n, -1);
        for (int i=0; i<n; i++) { adjList.push_back(Bucket()); }
        for (const pair<int, int>& pft : edges) {
            adjList[pft.first].insert(pft.second);
            adjList[pft.second].insert(pft.first);
        }
    }
    
    bool dfs(int parent, int node, int ccpar) {
        visited[node]  = true;
        ccParent[node] = ccpar;
        for (const int& neigh : adjList[node]) {
            if (neigh == parent) continue; //skip parent
            if (visited[neigh]) return false;
            if (dfs(node, neigh, ccpar) == false) return false;
        }
        return true;
    }
    
public:

    bool validTree(int n, vector<pair<int, int>>& edges) {
        initialize(n, edges);
        
        for (int n=0; n<adjList.size(); n++) {
            if (visited[n]) continue;
            if (dfs(-1, n, n) == false) return false; //detected cycle
        }
        int ccpar = ccParent[0];
        for (int i=1; i<adjList.size(); i++) {
            if (ccParent[i] != ccpar) return false; //not one connected component
        }
        return true;
    }
};
