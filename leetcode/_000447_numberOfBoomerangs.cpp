#pragma GCC optimize ("O2")
class Solution {
    double getDist(const vector<vector<int>>& points, int i, int j) {
        int dx = points[i][0] - points[j][0];
        int dy = points[i][1] - points[j][1];
        double d = std::sqrt(dx*dx + dy*dy);        
        return d;
    }
public:
    
    int numberOfBoomerangs(vector<vector<int>>& points) {
        // outer key: dist
        // inner key: index i
        // value: count of j/k etc. at dist from i
        map<double, map<int, int>> dist;
        for (int i=0; i<points.size(); i++) {
            for (int j=0; j<points.size(); j++) {
                if (i == j) continue;
                double d = getDist(points, i, j);
                dist[d][i]++;
            }
        }
        
        int count=0;
        for (const auto& kv : dist) {
            for (const auto& id : kv.second) {
                if (id.second <= 1) continue;
                int my_freq = id.second;
                int my_count = (my_freq) * (my_freq-1);
                count += my_count;
            }
        }
        return count;
    }
};
