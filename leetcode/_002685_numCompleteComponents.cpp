class Solution {
    unordered_map<int, unordered_set<int>> vedges;
    vector<int> vertices;

    void visit(int vertex, int c) {
        for (int e : vedges[vertex]) {
            if (vertices[e] == c) continue;
            assert(vertices[e] == 0);
            vertices[e] = c;
            visit(e, c);
        }
    }

    bool checkConnected(int color) {
        set<int> comp;
        for (int i=0; i<vertices.size(); i++) {
            if (vertices[i] == color) {
                comp.insert(i);
            }
        }
        int num = comp.size();
        for (int v : comp) {
            if (vedges[v].size() != num-1) return false;
        }
        return true;
    }
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        for (int i=0; i<n; i++) {
            vedges[i] = {};
        }
        for (const vector<int>& edge : edges) {
            vedges[edge[0]].insert(edge[1]);
            vedges[edge[1]].insert(edge[0]);
        }
        int color=1;
        vertices = vector<int>(n, 0);
        for (int i=0; i<n; i++) {
            if (vertices[i] != 0) continue;  // already colored
            visit(i, color);
            color++;
        }
        int count=0;
        for (int c=1; c<color; c++) {
            if (checkConnected(c)) count++;
        }
        return count;
    }
};
