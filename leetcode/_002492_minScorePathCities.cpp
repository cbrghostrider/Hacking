
class Solution {
    unordered_map<int, unordered_map<int, int>> adjlist;

public:
    int minScore(int n, vector<vector<int>>& roads) {
        for (const auto& road : roads) {
            int rd0 = road[0]-1;
            int rd1 = road[1]-1;
            adjlist[rd0][rd1] = road[2];
            adjlist[rd1][rd0] = road[2];
        }

        int minval = std::numeric_limits<int>::max();
        unordered_set<int> visited;
        queue<int> vertices;
        vertices.push(0);

        while (!vertices.empty()) {
            int vert = vertices.front();
            vertices.pop();
            visited.insert(vert);
            for (const auto& kv : adjlist[vert]) {
                minval = std::min(minval, kv.second);                
                if (visited.find(kv.first) != visited.end()) continue;
                visited.insert(kv.first);
                vertices.push(kv.first);
            }
        }
        return minval;
    }
};
