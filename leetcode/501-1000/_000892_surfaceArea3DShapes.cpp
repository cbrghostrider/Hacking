class Solution {
public:
    // O(n^2) time, O(1) space.
    int surfaceArea(vector<vector<int>>& grid) {
        int area = 0;
        const int M = grid.size();
        const int N = grid[0].size();
        for (int mi=0; mi<M; mi++) {
            for (int ni=0; ni<N; ni++) {
                if (grid[mi][ni] == 0) continue;
                int ht = grid[mi][ni];
                
                int ht_m_prev = (mi == 0 ? 0 : grid[mi-1][ni]);
                int ht_m_next = (mi == M-1 ? 0 : grid[mi+1][ni]);
                int ht_n_prev = (ni == 0 ? 0 : grid[mi][ni-1]);
                int ht_n_next = (ni == N-1 ? 0 : grid[mi][ni+1]);
                
                if (ht_m_prev < ht) {area += ht - ht_m_prev;}
                if (ht_m_next < ht) {area += ht - ht_m_next;}
                if (ht_n_prev < ht) {area += ht - ht_n_prev;}
                if (ht_n_next < ht) {area += ht - ht_n_next;}
                area += 2; // bottom and top always counted
            }
        }
        return area;
    }
};
