class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> ans;
        vector<int> last = {rStart, cStart};
        ans.push_back(last);

        int total=rows*cols-1;
        int width = 2;
        
        auto addInBounds = [rows, cols, &ans, &total](const vector<int>& coord) {
            if (coord[0] < 0 || coord[0] >= rows) return;
            if (coord[1] < 0 || coord[1] >= cols) return;
            if (total > 0) ans.push_back(coord);
            total--;
        };
        
        while (total > 0) {
            // Push right vertical segment
            last[1]++;  // turn right
            for (int i=0; i<width; i++) {
                addInBounds(last);
                if (i != width-1) last[0]++;
            }
            
            // Push bottom horizontal segment
            last[1]--;  // turn left
            for (int i=0; i<width; i++) {
                addInBounds(last);
                if (i != width-1) last[1]--;
            }
            
            // Push left vertical segment
            last[0]--;  // turn up
            for (int i=0; i<width; i++) {
                addInBounds(last);
                if (i != width-1) last[0]--;
            }
            
            // Push top horizontal segment
            last[1]++;  // turn right
            for (int i=0; i<width; i++) {
                addInBounds(last);
                if (i != width-1) last[1]++;
            }
                
            width += 2;
        }
        return ans;
    }
};
