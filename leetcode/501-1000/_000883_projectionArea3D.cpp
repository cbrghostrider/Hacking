class Solution {
    int N = 0;
    int xy = 0;
    int xz = 0;
    int yz = 0;
    
    // for each x==i, what is the max height tower.
    vector<int> x_ht;
    
    // for each y==i, what is the max height tower.
    vector<int> y_ht;
public:
    // O(n^2) time, O(n) space.
    int projectionArea(vector<vector<int>>& grid) {
        N = grid.size();
        y_ht = x_ht = vector<int>(N, 0);
        
        for (int xi=0; xi<N; xi++) {
            for (int yi=0; yi<N; yi++) {
                if (grid[xi][yi] != 0) { xy++; }
                if (grid[xi][yi] > x_ht[xi]) {x_ht[xi] = grid[xi][yi];}
                if (grid[xi][yi] > y_ht[yi]) {y_ht[yi] = grid[xi][yi];}
            }
        }
        for (int i=0; i<N; i++) {
            yz += x_ht[i];
            xz += y_ht[i];
        }
        
        return xy + xz + yz;
    }
};
