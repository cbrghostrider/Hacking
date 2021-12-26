class Solution {
    struct Coord {
        int r=0, c=0;
    };
    struct Info {
        Coord crd;
        int dist=0;
    };
public:
    // O(R*C) time, O(R*C) space.
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        const int R=mat.size();
        const int C=mat[0].size();
        vector<vector<int>> ans = mat;
        
        std::queue<Info> q;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (mat[r][c] == 0) {
                    q.push({{r, c}, 0});
                } else {
                    ans[r][c] = -1;
                }
            } 
        }
        
        while (!q.empty()) {
            auto elem=q.front(); q.pop();
            Coord crd = elem.crd;
            if (ans[crd.r][crd.c] != -1 && ans[crd.r][crd.c] != 0) continue;
            ans[crd.r][crd.c] = elem.dist;
            
            vector<Coord> neighs = {
                {crd.r-1, crd.c}, {crd.r+1, crd.c}, {crd.r, crd.c-1}, {crd.r, crd.c+1}
            };
            for (const Coord& neigh : neighs) {
                if (neigh.r<0 || neigh.r>=R || neigh.c<0 || neigh.c>=C) continue;
                if (ans[neigh.r][neigh.c] != -1) continue;
                q.push({neigh, elem.dist+1});
            }
        }
        
        return ans;
    }
};
