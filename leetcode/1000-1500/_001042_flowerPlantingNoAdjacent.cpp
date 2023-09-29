class Solution {
    
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& p) {
        vector<vector<int>> paths(n+1, vector<int>());
        vector<int> color(n+1, 0);
        
        for (int i=0; i<p.size(); i++) {
            paths[p[i][0]].push_back(p[i][1]);
            paths[p[i][1]].push_back(p[i][0]);
        }
        
        auto check = [&color, n]() -> int {
            for (int i=1; i<=n; i++) {
                if (color[i] == 0) return i;
            }
            return 0;
        };
        
        int start=0;
        while ((start = check()) != 0) {
            std::queue<int> q;
            q.push(start);
            
            while (!q.empty()) {
                int garden = q.front(); q.pop();
                if (color[garden] != 0) continue;
                
                unordered_set<int> pcolors;                
                for (int p : paths[garden]) {
                    if (color[p] != 0) {pcolors.insert(color[p]);}
                    else q.push(p);
                }
                vector<int> choices = {1, 2, 3, 4};
                for (int c : choices) {
                    if (pcolors.find(c) != pcolors.end()) continue;
                    color[garden] = c;
                    break;
                }
            }
        }
        
        color.erase(begin(color));
        return color;
    }
};
