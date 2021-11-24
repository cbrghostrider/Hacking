class Solution {
    class QuadLong {
      public:
        QuadLong() : nums(4, 0) {}
        
        // Returns the intersection (bitwise &) with rhs QuadLong.
        QuadLong operator&(const QuadLong& rhs) {
            QuadLong result;
            for (int i=0; i<4; i++) {
                result.nums[i] = nums[i] & rhs.nums[i];
            }
            return result;    
        }
        
        // Returns the number of 1s in this QuadLong.
        int popCnt() const {
            int count=0;
            for (int i=0; i<4; i++) {
                uint64_t mask = 0x1;
                for (int b=0; b<64; b++) {
                    count += ((mask & nums[i]) == 0 ? 0 : 1);
                    mask <<= 1;
                }
            }
            return count;
        }
        
        bool get(int pos) const {
            int ind_b = pos/64;
            int ind_s = pos%64;
            if (ind_b >= 4) return false;  // won't perform operation on overflow
            
            uint64_t mask = (((uint64_t)0x1) << ind_s);
            return (nums[ind_b] & mask);
        }
        
        QuadLong& set(int pos) {
            int ind_b = pos/64;
            int ind_s = pos%64;
            if (ind_b >= 4) return *this;  // won't perform operation on overflow
            
            uint64_t mask = (((uint64_t)0x1) << ind_s);
            nums[ind_b] |= mask;
            return *this;
        }
        
      private:
        vector<uint64_t> nums;
    };
public:
    
    // O(m*m*n) time, O(n^2) space.
    int countCornerRectangles(vector<vector<int>>& grid) {
        const int M = grid.size();
        const int N = grid[0].size();
        
        // Stores the QuadLong of 1's pattern up of cell (x, y).
        vector<vector<QuadLong>> ones_ydir(M, vector<QuadLong>(N, QuadLong()));  // upward gacing
        
        // Initialize quadlongs.
        for (int x=0; x<M; x++) {
            QuadLong ql;
            for (int y=0; y<N; y++) {
                if (grid[x][y]) {ql.set(y);}
                ones_ydir[x][y] = ql;
            }
        }
        
        int total_count = 0;
        // For all rectangles with (x,y) as their lower right,
        // find all rectangles that work.
        // By definition, x==0, and y==0, are skipped.
        for (int x=1; x<M; x++) {
            for (int y=1; y<N; y++) {
                if (grid[x][y] == 0) continue;
                for (int xp=x-1; xp>=0; xp--) {
                    if (grid[xp][y] == 0) continue;
                    QuadLong ql = ones_ydir[x][y] & ones_ydir[xp][y];
                    int count = ql.popCnt() - 1;
                    assert(count >= 0);
                    total_count += count;
                }
            }
        }
        
        return total_count;
    }
}; 
