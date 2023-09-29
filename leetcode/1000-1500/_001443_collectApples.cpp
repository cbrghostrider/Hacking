class Solution {
    // node -> (left, right) ; 
    unordered_map<int, vector<int>> tree;
    vector<bool> apples;
    vector<bool> visited;
    
    // return value says (visit_me?, my_cost)
    pair<int, bool> minCost(int node) {
        visited[node] = true;
        int stree_cost=0;
        for (int n : tree[node]) {
            if (visited[n]) continue;
            pair<int, bool> child = minCost(n);
            if (child.second) {
                stree_cost += 2 + child.first;
            }
        }
        if (stree_cost == 0 && apples[node]) {
           return {0, true};
        }
        return {stree_cost, stree_cost != 0};
    }
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        apples = hasApple;
        visited = vector<bool>(apples.size(), false);
        for (const auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        
        return minCost(0).first;
    }
};
